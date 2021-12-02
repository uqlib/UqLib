//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//
// getPngSizeメソッドは「https://w.atwiki.jp/miracle_mikuru/pages/133.html」を参考にした
//-----------------------------------------------------
#include <wincodec.h>
//	#include <string.h>
//	#include <stdlib.h>
#include "GraphicsManager.h"
#include "DirectXManager.h"
#include "FileManager.h"
#include "Constants.h"
#include "Logger.h"

#pragma warning(disable: 4996)

using namespace std;
using namespace Microsoft::WRL;

namespace uq_lib {

	GraphicsManager* GraphicsManager::m_gm = NULL;
	bool GraphicsManager::m_destroyFlg = true; // Phoenix Singleton回避用

	GraphicsManager::GraphicsManager() {
		m_textureId = 0;
		m_fontId = 0;
	}

	GraphicsManager::~GraphicsManager() {
	}

	int GraphicsManager::Init(
		HWND hWnd,
		ComPtr<ID3D11DeviceContext> d3d11DeviceContext,
		ComPtr<ID3D11RenderTargetView> d3d11RenderTargetView,
		ComPtr<ID2D1DeviceContext> d2d1DeviceContext,
		ComPtr<IDXGISwapChain> dxgiSwapChain,
		ID2D1SolidColorBrush* pBrush,
		int width,
		int height
	) {
		HRESULT hr = S_OK;
		m_hwnd = hWnd;
		m_pD3d11DeviceContext = d3d11DeviceContext;
		m_pD3d11RenderTargetView = d3d11RenderTargetView;
		m_pD2d1DeviceContext = d2d1DeviceContext;
		m_pDxgiSwapChain = dxgiSwapChain;
		m_width = width;
		m_height = height;

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWR_Factory));

		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if (FAILED(hr))
		{
			return -1;
		}

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_pImagingFactory));
		if (FAILED(hr))
		{
			return -1;
		}

		CreateFontContener(DEFAULT_FONT_SIZE, L"ＭＳ ゴシック");

		return 0;
	}

	void GraphicsManager::ReleaseAll() {
		ReleaseAllTexture();
		SAFE_RELEASE(m_pD3d11RenderTargetView);
		SAFE_RELEASE(m_pDxgiSwapChain);
		SAFE_RELEASE(m_pD2d1DeviceContext);
		SAFE_RELEASE(m_pD3d11DeviceContext);
		CoUninitialize();
	}

	void GraphicsManager::ReleaseAllTexture() {
		if (m_textures.empty()) return;
		for (auto itr = m_textures.begin(); itr != m_textures.end(); ++itr) {
			SAFE_RELEASE(itr->pBitmap);
		}
		m_textures.clear();
	}

	void GraphicsManager::ReleaseAllFont() {
		if (m_fonts.empty()) return;
		for (auto itr = m_fonts.begin(); itr != m_fonts.end(); ++itr) {
			SAFE_RELEASE(itr->pFont);
		}
		m_fonts.clear();
	}

	int GraphicsManager::BeginDrawing() {
		// D3D11で画面をクリアしてD2D1で描画
		const float color[] = { 0.f, 0.f, 0.f, 1.f };
		m_pD3d11DeviceContext->ClearRenderTargetView(m_pD3d11RenderTargetView.Get(), color);

		m_pD2d1DeviceContext->BeginDraw();
		return 0;
	}

	int GraphicsManager::EndDrawing() {
		m_pD2d1DeviceContext->EndDraw();
		m_pDxgiSwapChain->Present(1, 0);
		return 0;
	}

	int GraphicsManager::CreateFontContener(int height, wstring fontName) {
		FontContener fc;
		fc.height = height;
		fc.fontId = m_fontId;

		m_pDWR_Factory->CreateTextFormat(
			fontName.c_str(),
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			(float)height,
			L"",
			&fc.pFont
		);

		//if (hr != 0) {
		//	Logger::OutputDebug("ERR D3DXCreateFont hr : " + to_string(hr));
		//}

		m_fonts.push_back(fc);
		m_fontId++;
		return fc.fontId;
	}

	bool getPngSize(LPCTSTR path, UINT* width, UINT* height)
	{
		FILE* f = fopen(path, "rb");
		if(!f) return false;

		BYTE header[8];// PNGファイルシグネチャ
		if(fread(header, sizeof(BYTE), 8, f) < 8){ fclose(f); return false; }

		const static BYTE png[] = { 0x89, 'P', 'N', 'G', 0x0d, 0x0a, 0x1a, 0x0a };
		if(memcmp(header, png, 8) != 0){ fclose(f); return false; }

		BYTE ihdr[25];// IHDRチャンク(イメージヘッダ)
		if(fread(ihdr, sizeof(BYTE), 25, f) < 25){ fclose(f); return false; }

		// length = 13 (0x0D)
		const static BYTE length[] = { 0x00, 0x00, 0x00, 0x0D };
		if(memcmp(ihdr, length, 4) != 0){ fclose(f); return false; }

		// IHDR
		if(memcmp(ihdr+4, "IHDR", 4) != 0){ fclose(f); return false; }

		BYTE* p;

		DWORD w;
		p = (BYTE*)&w;
		p[0] = ihdr[8+3];
		p[1] = ihdr[8+2];
		p[2] = ihdr[8+1];
		p[3] = ihdr[8+0];

		DWORD h;
		p = (BYTE*)&h;
		p[0] = ihdr[12+3];
		p[1] = ihdr[12+2];
		p[2] = ihdr[12+1];
		p[3] = ihdr[12+0];

		*width  = (UINT)w;
		*height = (UINT)h;

		fclose(f);
		return true;
	}

	int GraphicsManager::CreateTextureFromFile(wstring wFileName, string fileName) {
		HRESULT hr = S_OK;

		TextureContener tc;
		IWICBitmapDecoder* dec;
		// デコード
		hr = m_pImagingFactory->CreateDecoderFromFilename(
			wFileName.c_str(),
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&dec
		);
		if (FAILED(hr)) {
			Logger::OutputWarn("CreateDecoderFromFilenameに失敗。");
			return -1;
		}

		IWICBitmapFrameDecode* frame;

		// フレームを取得
		dec->GetFrame(0, &frame);

		IWICFormatConverter* converter;
		// 画像イメージをDirect2D形式にコンバート
		hr = m_pImagingFactory->CreateFormatConverter(&converter);
		if (FAILED(hr)) {
			Logger::OutputWarn("CreateFormatConverterに失敗。");
			return -1;
		}

		// 画像の転送自体は終了
		hr = converter->Initialize(frame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
		if (FAILED(hr)) {
			Logger::OutputWarn("Initializeに失敗。");
			return -1;
		}

		SAFE_RELEASE(dec);
		SAFE_RELEASE(frame)

		ID2D1Bitmap* pBitmap = NULL;
		hr = m_pD2d1DeviceContext->CreateBitmapFromWicBitmap(converter, NULL, &pBitmap);
		if (FAILED(hr)) {
			Logger::OutputWarn("CreateBitmapFromWicBitmapに失敗。");
			return -1;
		}

		if (pBitmap != NULL) {
			UINT width;
			UINT height;
			getPngSize(fileName.c_str(), &width, &height);
			//D2D1_SIZE_F d2d1Size = pBitmap->GetSize(); MinGWでGetSize()は異常値が返るので使えない
			tc.textureId = m_textureId;
			tc.pBitmap = pBitmap;
			tc.loadCnt = 1;
			tc.width = (float)width;
			tc.height = (float)height;
			m_textures.push_back(tc);
			m_textureId++;
			return tc.textureId;
		}
		return -1;
	}

	int GraphicsManager::CreateTextureFromDatFile(string fileName) {
		long size = 0;
		char* buffer = 0;
		int result = FileManager::GetInstance()->LoadFileFromDatFile(fileName, &buffer, &size);

		HRESULT hr = S_OK;
		TextureContener tc;
		IWICBitmapDecoder* dec;

		// デコード
		IWICStream* pStream;
		hr = m_pImagingFactory->CreateStream(&pStream);
		if (FAILED(hr))
		{
			Logger::OutputWarn("CreateStreamに失敗。");
			return -1;
		}
		if (buffer == NULL){
			Logger::OutputWarn("bufferがNULL。");
			return -1;
		}
		hr = pStream->InitializeFromMemory((byte*)buffer, size);
		if (FAILED(hr))
		{
			Logger::OutputWarn("InitializeFromMemoryに失敗。");
			return -1;
		}
		hr = m_pImagingFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&dec);
		if (FAILED(hr))
		{
			Logger::OutputWarn("CreateDecoderFromStreamに失敗。");
			return -1;
		}

		IWICBitmapFrameDecode* frame;

		// フレームを取得
		dec->GetFrame(0, &frame);

		IWICFormatConverter* converter;
		// 画像イメージをDirect2D形式にコンバート
		hr = m_pImagingFactory->CreateFormatConverter(&converter);
		if (FAILED(hr))
		{
			Logger::OutputWarn("CreateFormatConverterに失敗。");
			return -1;
		}

		// 画像の転送自体は終了
		hr = converter->Initialize(frame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL, 0.f,
			WICBitmapPaletteTypeMedianCut
		);
		if (FAILED(hr))
		{
			Logger::OutputWarn("Initializeに失敗。");
			return -1;
		}

		SAFE_RELEASE(dec);
		SAFE_RELEASE(frame);

		ID2D1Bitmap* pBitmap = NULL;
		hr = m_pD2d1DeviceContext->CreateBitmapFromWicBitmap(converter, NULL, &pBitmap);
		if (FAILED(hr))
		{
			Logger::OutputWarn("CreateBitmapFromWicBitmapに失敗。");
			return -1;
		}

		if (pBitmap != NULL) {
			D2D1_SIZE_F d2d1Size = pBitmap->GetSize();
			tc.textureId = 99;
			tc.pBitmap = pBitmap;
			tc.loadCnt = 1;
			tc.width = d2d1Size.width;
			tc.height = d2d1Size.height;

			m_textures.push_back(tc);
			m_textureId++;
		}
		return 0;
	}

	GraphicsManager::TextureContener GraphicsManager::GetTextureContener(int graphicId) {
		TextureContener tc; // テクスチャが登録されていない場合はTextureIdを参照しチェックを行うこと
		tc.textureId = -1;
		if (m_textures.empty()) return tc;

		for (auto itr = m_textures.begin(); itr != m_textures.end(); ++itr) {
			if (itr->textureId == graphicId) {

				return *itr;
			}
		}
		return tc;
	}

	int GraphicsManager::DrawTexture(int graphicId, int x, int y, float opacity) {
		TextureContener tc = GetTextureContener(graphicId);
		if (tc.textureId == -1) {
			return -1;
		}
		// 描画矩形(コピー先)
		D2D1_RECT_F oDrawRect = D2D1::RectF((float)x, (float)y, x + tc.width, y + tc.height);
		// 描画矩形(コピー元)
		D2D1_RECT_F oSrcDrawRect = D2D1::RectF(0, 0, tc.width, tc.height);
		m_pD2d1DeviceContext->DrawBitmap(
			tc.pBitmap,
			oDrawRect,
			opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			&oSrcDrawRect     // 描画元矩形(これを調整してトリミングします)
		);
		return 0;
	}

	int GraphicsManager::DrawTexture(int graphicId, int x, int y, int sx, int sy, int sw, int sh, float opacity) {
		TextureContener tc = GetTextureContener(graphicId);
		if (tc.textureId == -1) {
			return -1;
		}
		// 描画矩形(コピー先)
		D2D1_RECT_F oDrawRect = D2D1::RectF((float)x, (float)y, (float)(x + sw), (float)(y + sh));
		// 描画矩形(コピー元)
		D2D1_RECT_F oSrcDrawRect = D2D1::RectF((float)sx, (float)sy, (float)(sx + sw), (float)(sy + sh));
		m_pD2d1DeviceContext->DrawBitmap(
			tc.pBitmap,
			oDrawRect,
			opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			&oSrcDrawRect     // 描画元矩形(これを調整してトリミングします)
		);
		return 0;
	}

	GraphicsManager::FontContener GraphicsManager::GetFontContener(int fontId) {
		FontContener fc;
		fc.fontId = -1;
		if (m_fonts.empty()) return fc;

		for (auto itr = m_fonts.begin(); itr != m_fonts.end(); ++itr) {
			if (itr->fontId == fontId) {

				return *itr;
			}
		}
		return fc;
	}

	int GraphicsManager::DrawString(int x, int y, string text, int fontId, UINT32 hexColorCode, float opacity) {
		FontContener fc = GetFontContener(fontId);

		wchar_t wbuf[256]; MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, wbuf, 256);
		
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			m_pD2d1DeviceContext->DrawTextA(
				wbuf
				, (int)wcslen(wbuf)
				, fc.pFont
				, D2D1::RectF((float)x, (float)y, (float)m_width, (float)m_height)
				, pBrush
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			m_pD2d1DeviceContext->DrawLine(
				D2D1::Point2F((float)x, (float)y),
				D2D1::Point2F((float)(x + ax), (float)(y + ay)),
				pBrush,
				width
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::DrawSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_RECT_F rect = D2D1::RectF(
				(float)x,
				(float)y,
				(float)(x + ax),
				(float)(y + ay)
			);
			m_pD2d1DeviceContext->DrawRectangle(
				rect
				, pBrush
				, strokeWidth
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::FillSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_RECT_F rect = D2D1::RectF(
				(float)x,
				(float)y,
				(float)(x + ax),
				(float)(y + ay)
			);
			m_pD2d1DeviceContext->FillRectangle(
				rect
				, pBrush
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::DrawRoundedSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth, float radius, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_ROUNDED_RECT rect = D2D1::RoundedRect(
				D2D1::RectF(
					(float)x
					, (float)y
					, (float)(x + ax)
					, (float)(y + ay)
				)
				, radius
				, radius
			);
			m_pD2d1DeviceContext->DrawRoundedRectangle(
				rect
				, pBrush
				, strokeWidth
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::FillRoundedSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float radius, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_ROUNDED_RECT rect = D2D1::RoundedRect(
				D2D1::RectF(
					(float)x
					, (float)y
					, (float)(x + ax)
					, (float)(y + ay)
				)
				, radius
				, radius
			);
			m_pD2d1DeviceContext->FillRoundedRectangle(
				rect
				, pBrush
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_ELLIPSE ellipse = D2D1::Ellipse(
				D2D1::Point2F((float)x, (float)y),
				(float)width,
				(float)height
			);
			m_pD2d1DeviceContext->DrawEllipse(
				ellipse
				, pBrush
				, strokeWidth
			);
			pBrush->Release();
		}
		return 0;
	}

	int GraphicsManager::FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float opacity) {
		ID2D1SolidColorBrush* pBrush = NULL;
		m_pD2d1DeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(hexColorCode, opacity)
			, &pBrush
		);
		if (pBrush != NULL) {
			D2D1_ELLIPSE ellipse = D2D1::Ellipse(
				D2D1::Point2F((float)x, (float)y),
				(float)width,
				(float)height
			);
			m_pD2d1DeviceContext->FillEllipse(
				ellipse
				, pBrush
			);
			pBrush->Release();
		}
		return 0;
	}
}

//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_GRAPHICSMANAGER_H
#define UQ_LIB_GRAPHICSMANAGER_H

#include <string>
#include <vector>

#include <wrl/client.h>
#include <d2d1_1.h>
#include <d3d11.h>

namespace uq_lib {

	class GraphicsManager
	{
	public:
		struct TextureContener {
			int textureId;
			int loadCnt;					// テクスチャロードカウンタ
			ID2D1Bitmap* pBitmap;			// ビットマップ
			float width;					// 幅
			float height;					// 高さ
		};

		struct FontContener {
			int fontId;
			int height;
			IDWriteTextFormat* pFont;	// フォント実体
		};

		/**
		 * インスタンス取得
		 *
		 * @return インスタンス
		 */
		static GraphicsManager* GetInstance() {
			if (!m_gm && m_destroyFlg == true) m_gm = new GraphicsManager();
			return m_gm;
		}

		/**
		 * 破棄
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_gm;
			m_gm = NULL;
		}

		/**
		 * デストラクタ
		 */
		virtual ~GraphicsManager();

		/**
		 * 初期化
		 *
		 * @param device デバイス
		 * @return 成功（0）、失敗（-1）
		 */
		int Init(HWND hWnd,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3d11DeviceContext,
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> d3d11RenderTargetView,
			Microsoft::WRL::ComPtr<ID2D1DeviceContext> d2d1DeviceContext,
			Microsoft::WRL::ComPtr<IDXGISwapChain> dxgiSwapChain,
			ID2D1SolidColorBrush* pBrush,
			int width,
			int height
		);

		/**
		 * 全リリース
		 */
		void ReleaseAll();

		/**
		 * 全テクスチャリリース
		 */
		void ReleaseAllTexture();

		/**
		 * 全フォントリリース
		 */
		void ReleaseAllFont();

		/**
		 * 描画開始
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int BeginDrawing();

		/**
		 * 描画終了
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int EndDrawing();

		/**
		 * フォントコンテナ作成
		 *
		 * @param height   文字の高さ
		 * @param fontName フォント名
		 * @return フォントID
		 */
		int CreateFontContener(int height, std::wstring fontName);

		/**
		 * ファイルからテクスチャ作成
		 *
		 * @param fileName ファイル名
		 * @return テクスチャID
		 */
		int CreateTextureFromFile(std::wstring fileName);

		/**
		 * Datファイルからテクスチャ作成
		 *
		 * @param fileName ファイル名
		 * @return テクスチャID
		 */
		int CreateTextureFromDatFile(std::string fileName);

		/**
		 * テクスチャ描画
		 *
		 * @param graphicId グラフィックID
		 * @param x         座標X
		 * @param y         座標Y
		 * @param opacity   不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawTexture(int graphicId, int x, int y, float opacity = 1.0);

		/**
		 * テクスチャ描画
		 *
		 * @param graphicId グラフィックID
		 * @param x         転送先X座標
		 * @param y         転送先Y座標
		 * @param sx        転送元X座標
		 * @param sy        転送元Y座標
		 * @param sw        転送元矩形サイズ（幅）
		 * @param sh        転送元矩形サイズ（高さ）
		 * @param opacity   不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawTexture(int graphicId, int x, int y, int sx, int sy, int sw, int sh, float opacity = 1.0);

		/**
		 * 文字列描画
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param text          文字列
		 * @param fontId        フォントID
		 * @param hexColorCode  16進数カラーコード
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawString(int x, int y, std::string text, int fontId, UINT32 hexColorCode, float opacity = 1.0);

		/**
		 * ライン描画
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param ax            追加X座標
		 * @param ay            追加Y座標
		 * @param hexColorCode  16進数カラーコード
		 * @param width         幅
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity = 1.0);

		/**
		 * 四角形描画
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param ax            追加X座標
		 * @param ay            追加Y座標
		 * @param hexColorCode  16進数カラーコード
		 * @param strokeWidth   線の太さ
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float opacity = 1.0);

		/**
		 * 四角形描画（塗りつぶし）
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param ax            追加X座標
		 * @param ay            追加Y座標
		 * @param hexColorCode  16進数カラーコード
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int FillSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float opacity = 1.0);

		/**
		 * 丸め四角形描画
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param ax            追加X座標
		 * @param ay            追加Y座標
		 * @param hexColorCode  16進数カラーコード
		 * @param strokeWidth   線の太さ
		 * @param radius        0：角のまま　、0.1以上（角を丸める）
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius, float opacity = 1.0);

		/**
		 * 丸め四角形描画（塗りつぶし）
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param ax            追加X座標
		 * @param ay            追加Y座標
		 * @param hexColorCode  16進数カラーコード
		 * @param radius        0：角のまま　、0.1以上（角を丸める）
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int FillRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius, float opacity = 1.0);

		/**
		 * 楕円描画
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param width         幅（半径）
		 * @param height        高さ（半径）
		 * @param hexColorCode  16進数カラーコード
		 * @param strokeWidth   線の太さ
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity = 1.0);

		/**
		 * 楕円描画（塗りつぶし）
		 *
		 * @param x             X座標
		 * @param y             Y座標
		 * @param width         幅（半径）
		 * @param height        高さ（半径）
		 * @param hexColorCode  16進数カラーコード
		 * @param opacity       不透明度（透明 0.0f ～ 1.0f 不透明）
		 * @return 成功（0）、失敗（-1）
		 */
		int FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float opacity = 1.0);
		
	private:
		// シングルトン
		static GraphicsManager* m_gm;
		static bool m_destroyFlg; // Phoenix Singleton回避用
		std::vector<TextureContener> m_textures;
		std::vector<FontContener> m_fonts;
		int m_textureId;
		int m_fontId;
		int m_width;
		int m_height;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pD3d11DeviceContext = NULL;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pD3d11RenderTargetView = NULL;
		
		// Direct2D 1.1からはID2D1DeviceContext。それ以前はID2D1HwndRenderTarget。
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_pD2d1DeviceContext = NULL;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_pDxgiSwapChain = NULL;
		IWICImagingFactory* m_pImagingFactory = NULL;//画像表示用
		IDWriteFactory* m_pDWR_Factory = NULL;
		HWND m_hwnd = NULL;

		/**
		 * コンストラクタ
		 */
		GraphicsManager();

		/**
		 * テクスチャコンテナ取得
		 *
		 * @param graphicId グラフィックID
		 * @return テクスチャコンテナ
		 */
		TextureContener GetTextureContener(int graphicId);

		/**
		 * フォントコンテナ取得
		 *
		 * @param fontId フォントID
		 * @return フォントコンテナ
		 */
		FontContener GetFontContener(int fontId);
	};
}

#endif // UQ_LIB_GRAPHICSMANAGER_H

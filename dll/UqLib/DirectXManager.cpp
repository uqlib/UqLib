//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include "DirectXManager.h"
#include "GraphicsManager.h"

using namespace std;

namespace uq_lib {

	DirectXManager* DirectXManager::m_dm = NULL;
	bool DirectXManager::m_destroyFlg = true; // Phoenix Singleton回避用

	DirectXManager::DirectXManager() {
	}

	DirectXManager::~DirectXManager() {
	}

	int DirectXManager::InitializeDirectX(HWND hWnd, int width, int height, bool isFullscreen) {
		// D3D11初期化
#ifdef _DEBUG
		const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_SINGLETHREADED;
#else
		const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif
		Microsoft::WRL::ComPtr<ID3D11Device> d3d11Device;
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0, D3D11_SDK_VERSION,
			&d3d11Device, nullptr, &m_d3d11DeviceContext);

		Microsoft::WRL::ComPtr<IDXGIDevice1> dxgiDevice;
		d3d11Device.As(&dxgiDevice);

		// D2D1初期化
		Microsoft::WRL::ComPtr<ID2D1Factory1> d2d1Factory;
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&d2d1Factory));

		Microsoft::WRL::ComPtr<ID2D1Device> d2d1Device;
		d2d1Factory->CreateDevice(dxgiDevice.Get(), &d2d1Device);

		d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_d2d1DeviceContext);

		// DXGIスワップチェインを作る
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		dxgiFactory->CreateSwapChain(d3d11Device.Get(), &swapChainDesc, &m_dxgiSwapChain);

		dxgiDevice->SetMaximumFrameLatency(1);

		// D2D1にレンダリングターゲットを登録
		Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
		m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));

		const auto bp = D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> d2d1Bitmap;
		m_d2d1DeviceContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bp, &d2d1Bitmap);

		m_d2d1DeviceContext->SetTarget(d2d1Bitmap.Get());

		// D3D11にレンダリングターゲットを設定
		Microsoft::WRL::ComPtr<ID3D11Texture2D> d3d11Texture;
		m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&d3d11Texture));

		d3d11Device->CreateRenderTargetView(d3d11Texture.Get(), nullptr, &m_d3d11RenderTargetView);

		// &pBrushは、文字列描画で使用する
		m_d2d1DeviceContext->CreateSolidColorBrush(D2D1::ColorF(0xffffff, 1.f), &m_pBrush);

		GraphicsManager::GetInstance()->Init(hWnd, m_d3d11DeviceContext, m_d3d11RenderTargetView, m_d2d1DeviceContext, m_dxgiSwapChain, m_pBrush, width, height);

		return 0;
	}
}
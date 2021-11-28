//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_DIRECTXMANAGER_H
#define UQ_LIB_DIRECTXMANAGER_H

#include <string>
#include <wrl/client.h>
#include <dwrite.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include "Constants.h"
#include "Logger.h"

namespace uq_lib {

	class DirectXManager
	{
	public:

		/**
		 * インスタンス取得
		 *
		 * @return インスタンス
		 */
		static DirectXManager* GetInstance() {
			if (!m_dm && m_destroyFlg == true) m_dm = new DirectXManager();
			return m_dm;
		}

		/**
		 * 破棄
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_dm;
			m_dm = NULL;
		}

		/**
		 * デストラクタ
		 */
		virtual ~DirectXManager();

		/** DirectX初期化
		 *
		 * @param hWnd         ウィンドウハンドル
		 * @param width        幅
		 * @param height       高さ
		 * @param isFullscreen フルスクリーン
		 * @return 成功（0）、失敗（-1）
		 */
		int InitializeDirectX(HWND hWnd, int width, int height, bool isFullscreen);

	private:

		// シングルトン
		static DirectXManager* m_dm;
		static bool m_destroyFlg; // Phoenix Singleton回避用

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3d11DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3d11RenderTargetView;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_d2d1DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_dxgiSwapChain;
		ID2D1SolidColorBrush* m_pBrush;
		IDWriteTextFormat* m_pFont;

		/** コンストラクタ
		 */
		DirectXManager();
	};
}

#endif // UQ_LIB_DIRECTXMANAGER_H

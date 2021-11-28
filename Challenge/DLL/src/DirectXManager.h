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
		 * �C���X�^���X�擾
		 *
		 * @return �C���X�^���X
		 */
		static DirectXManager* GetInstance() {
			if (!m_dm && m_destroyFlg == true) m_dm = new DirectXManager();
			return m_dm;
		}

		/**
		 * �j��
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_dm;
			m_dm = NULL;
		}

		/**
		 * �f�X�g���N�^
		 */
		virtual ~DirectXManager();

		/** DirectX������
		 *
		 * @param hWnd         �E�B���h�E�n���h��
		 * @param width        ��
		 * @param height       ����
		 * @param isFullscreen �t���X�N���[��
		 * @return �����i0�j�A���s�i-1�j
		 */
		int InitializeDirectX(HWND hWnd, int width, int height, bool isFullscreen);

	private:

		// �V���O���g��
		static DirectXManager* m_dm;
		static bool m_destroyFlg; // Phoenix Singleton���p

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3d11DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3d11RenderTargetView;
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_d2d1DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_dxgiSwapChain;
		ID2D1SolidColorBrush* m_pBrush;
		IDWriteTextFormat* m_pFont;

		/** �R���X�g���N�^
		 */
		DirectXManager();
	};
}

#endif // UQ_LIB_DIRECTXMANAGER_H

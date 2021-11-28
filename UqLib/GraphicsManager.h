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
			int loadCnt;					// �e�N�X�`�����[�h�J�E���^
			ID2D1Bitmap* pBitmap;			// �r�b�g�}�b�v
			float width;					// ��
			float height;					// ����
		};

		struct FontContener {
			int fontId;
			int height;
			IDWriteTextFormat* pFont;	// �t�H���g����
		};

		/**
		 * �C���X�^���X�擾
		 *
		 * @return �C���X�^���X
		 */
		static GraphicsManager* GetInstance() {
			if (!m_gm && m_destroyFlg == true) m_gm = new GraphicsManager();
			return m_gm;
		}

		/**
		 * �j��
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_gm;
			m_gm = NULL;
		}

		/**
		 * �f�X�g���N�^
		 */
		virtual ~GraphicsManager();

		/**
		 * ������
		 *
		 * @param device �f�o�C�X
		 * @return �����i0�j�A���s�i-1�j
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
		 * �S�����[�X
		 */
		void ReleaseAll();

		/**
		 * �S�e�N�X�`�������[�X
		 */
		void ReleaseAllTexture();

		/**
		 * �S�t�H���g�����[�X
		 */
		void ReleaseAllFont();

		/**
		 * �`��J�n
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int BeginDrawing();

		/**
		 * �`��I��
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int EndDrawing();

		/**
		 * �t�H���g�R���e�i�쐬
		 *
		 * @param height   �����̍���
		 * @param fontName �t�H���g��
		 * @return �t�H���gID
		 */
		int CreateFontContener(int height, std::wstring fontName);

		/**
		 * �t�@�C������e�N�X�`���쐬
		 *
		 * @param fileName �t�@�C����
		 * @return �e�N�X�`��ID
		 */
		int CreateTextureFromFile(std::wstring fileName);

		/**
		 * Dat�t�@�C������e�N�X�`���쐬
		 *
		 * @param fileName �t�@�C����
		 * @return �e�N�X�`��ID
		 */
		int CreateTextureFromDatFile(std::string fileName);

		/**
		 * �e�N�X�`���`��
		 *
		 * @param graphicId �O���t�B�b�NID
		 * @param x         ���WX
		 * @param y         ���WY
		 * @param opacity   �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawTexture(int graphicId, int x, int y, float opacity = 1.0);

		/**
		 * �e�N�X�`���`��
		 *
		 * @param graphicId �O���t�B�b�NID
		 * @param x         �]����X���W
		 * @param y         �]����Y���W
		 * @param sx        �]����X���W
		 * @param sy        �]����Y���W
		 * @param sw        �]������`�T�C�Y�i���j
		 * @param sh        �]������`�T�C�Y�i�����j
		 * @param opacity   �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawTexture(int graphicId, int x, int y, int sx, int sy, int sw, int sh, float opacity = 1.0);

		/**
		 * ������`��
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param text          ������
		 * @param fontId        �t�H���gID
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawString(int x, int y, std::string text, int fontId, UINT32 hexColorCode, float opacity = 1.0);

		/**
		 * ���C���`��
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param ax            �ǉ�X���W
		 * @param ay            �ǉ�Y���W
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param width         ��
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity = 1.0);

		/**
		 * �l�p�`�`��
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param ax            �ǉ�X���W
		 * @param ay            �ǉ�Y���W
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param strokeWidth   ���̑���
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float opacity = 1.0);

		/**
		 * �l�p�`�`��i�h��Ԃ��j
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param ax            �ǉ�X���W
		 * @param ay            �ǉ�Y���W
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int FillSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float opacity = 1.0);

		/**
		 * �ۂߎl�p�`�`��
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param ax            �ǉ�X���W
		 * @param ay            �ǉ�Y���W
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param strokeWidth   ���̑���
		 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float strokeWidth, float radius, float opacity = 1.0);

		/**
		 * �ۂߎl�p�`�`��i�h��Ԃ��j
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param ax            �ǉ�X���W
		 * @param ay            �ǉ�Y���W
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param radius        0�F�p�̂܂܁@�A0.1�ȏ�i�p���ۂ߂�j
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int FillRoundedSquare(int x, int y, int sx, int sy, UINT32 hexColorCode, float radius, float opacity = 1.0);

		/**
		 * �ȉ~�`��
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param width         ���i���a�j
		 * @param height        �����i���a�j
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param strokeWidth   ���̑���
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity = 1.0);

		/**
		 * �ȉ~�`��i�h��Ԃ��j
		 *
		 * @param x             X���W
		 * @param y             Y���W
		 * @param width         ���i���a�j
		 * @param height        �����i���a�j
		 * @param hexColorCode  16�i���J���[�R�[�h
		 * @param opacity       �s�����x�i���� 0.0f �` 1.0f �s�����j
		 * @return �����i0�j�A���s�i-1�j
		 */
		int FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float opacity = 1.0);
		
	private:
		// �V���O���g��
		static GraphicsManager* m_gm;
		static bool m_destroyFlg; // Phoenix Singleton���p
		std::vector<TextureContener> m_textures;
		std::vector<FontContener> m_fonts;
		int m_textureId;
		int m_fontId;
		int m_width;
		int m_height;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pD3d11DeviceContext = NULL;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pD3d11RenderTargetView = NULL;
		
		// Direct2D 1.1�����ID2D1DeviceContext�B����ȑO��ID2D1HwndRenderTarget�B
		Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_pD2d1DeviceContext = NULL;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_pDxgiSwapChain = NULL;
		IWICImagingFactory* m_pImagingFactory = NULL;//�摜�\���p
		IDWriteFactory* m_pDWR_Factory = NULL;
		HWND m_hwnd = NULL;

		/**
		 * �R���X�g���N�^
		 */
		GraphicsManager();

		/**
		 * �e�N�X�`���R���e�i�擾
		 *
		 * @param graphicId �O���t�B�b�NID
		 * @return �e�N�X�`���R���e�i
		 */
		TextureContener GetTextureContener(int graphicId);

		/**
		 * �t�H���g�R���e�i�擾
		 *
		 * @param fontId �t�H���gID
		 * @return �t�H���g�R���e�i
		 */
		FontContener GetFontContener(int fontId);
	};
}

#endif // UQ_LIB_GRAPHICSMANAGER_H

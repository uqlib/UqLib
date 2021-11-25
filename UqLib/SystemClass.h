//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_SYSTEMCLASS_H
#define UQ_LIB_SYSTEMCLASS_H

#include <windows.h>
#include <string>
#include <time.h>
#include <map>
#include "Constants.h"

namespace uq_lib {

	class SystemClass
	{
	public:

		/**
		 * ������
		 *
		 * @param title        �^�C�g��
		 * @param screenWidth  ��ʂ̕�
		 * @param screenHeight ��ʂ̍���
		 * @return �����i0�j�A���s�i-1�j
		 */
		int Initialize(std::string title, int screenWidth, int screenHeight);

		/**
		 * �E�B���h�E�X�V
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int UpdateWindow();

		/**
		 * ���b�Z�[�W�n���h��
		 *
		 * @param hWnd �E�B���h�E�n���h��
		 * @param message ���b�Z�[�W
		 * @param wParam w�p�����[�^
		 * @param lParam l�p�����[�^
		 * @return ���b�Z�[�W�����̌���
		 */
		static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		/**
		 * �A�v���I��
		 */
		void AppQuit();

		/**
		 * �I�����b�Z�[�W
		 *
		 * @return �I���ʒm�����Ă��Ȃ��i0�j�A�I���ʒm�����Ă���i-1�j
		 */
		int IsQuitMessage();

		/**
		 * �E�B���h�E�^�C�g���ݒ�
		 *
		 * @param title �^�C�g��
		 * @return �����i0�j�A���s�i-1�j
		 */
		int SetWindowTitle(std::string title);

		/**
		 * ���N���b�N�|�C���g�擾
		 *
		 * @param x X���W
		 * @param y Y���W
		 */
		void GetLeftClickPoint(int* x, int* y);

		/**
		 * �L�[�����������m�F
		 *
		 * @param keyCode �L�[�R�[�h
		 * @return 0�F�����Ă��Ȃ��A1�F������
		 */
		int CheckPressedKey(int keyCode);

		/**
		 * �L�[�������Ă��邩�m�F
		 *
		 * @param keyCode �L�[�R�[�h
		 * @return 0�F�����Ă��Ȃ��A1�F�����Ă���
		 */
		int CheckPressKey(int keyCode);

	private:

		static int m_message;
		static POINT m_clickPoint;
		LPCSTR m_applicationName = NULL;
		HINSTANCE m_hinstance;
		HWND m_hwnd;
		bool m_isQuitMessage; // �I���ʒm�����Ă��邩�H
		std::map<int, int> m_keyInputs;
		DWORD m_time;

		/**
		 * �E�B���h�E������
		 *
		 * @param title �^�C�g��
		 * @param screenWidth ��ʂ̕�
		 * @param screenHeight ��ʂ̍���
		 * @return �����i0�j�A���s�i-1�j
		 */
		int InitializeWindow(std::string title, int screenWidth, int screenHeight);

		/**
		 * �E�B���h�E���b�Z�[�W�X�V
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int UpdateWindowMessage();

		/**
		 * �L�[�{�[�h�̏�ԍX�V
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int UpdateKeyboardState();

		/**
		 * �L�[�X�V
		 *
		 * @param keyStates �L�[���
		 * @param sysKey    �V�X�e���L�[
		 * @param myKey     �}�C�L�[
		 * @return �����i0�j�A���s�i-1�j
		 */
		int UpdateKey(BYTE* keyStates, int sysKey, int myKey);

		/**
		 * �L�[�X�V
		 *
		 * @param chara  ����
		 * @param sysKey �V�X�e���L�[
		 * @param myKey  �}�C�L�[
		 * @return �����i0�j�A���s�i-1�j
		 */
		int UpdateKey2(char chara, int sysKey, int myKey);

		/**
		 * �N���C�A���g�̃E�B���h�E�T�C�Y�ύX
		 *
		 * @param hWnd   �E�B���h�E�n���h��
		 * @param width  ��
		 * @param height ����
		 * @return �����i0�j�A���s�i-1�j
		 */
		int WindowResizeByClient(HWND hWnd, int width, int height);
	};

	/**
	 * �E�B���h�E�v���V�[�W��
	 *
	 * @param hWnd     �E�B���h�E�n���h��
	 * @param uMessage ���b�Z�[�W
	 * @param wParam   w�p�����[�^
	 * @param lParam   l�p�����[�^
	 * @return �����i0�j�A���s�i-1�j
	 */
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
}

#endif // UQ_LIB_SYSTEMCLASS_H

//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_SOUNDMANAGER_H
#define UQ_LIB_SOUNDMANAGER_H

#include <windows.h>
#include <mutex>
#include <string>
#include <dsound.h>
#include "Logger.h"

namespace uq_lib {

	class SoundManager
	{
	public:

		/**
		 * �C���X�^���X�擾
		 *
		 * @return �C���X�^���X
		 */
		 // �C���X�^���X�擾
		static SoundManager* GetInstance() {
			if (!m_sm && m_destroyFlg == true) m_sm = new SoundManager();
			return m_sm;
		}

		/**
		 * �j��
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_sm;
			m_sm = NULL;
		}

		/**
		 * �f�X�g���N�^
		 */
		virtual ~SoundManager();


		/**
		 * ������
		 *
		 * @param hWnd �E�B���h�E�n���h��
		 * @return �����i0�j�A���s�i-1�j
		 */
		int Init(HWND hWnd);

		/**
		 * �t�@�C������T�E���h�Đ�
		 *
		 * @param fileName �t�@�C����
		 * @param playType �Đ��^�C�v
		 * @return �����i0�j�A���s�i-1�j
		 */
		int PlaySoundFromFile(std::string fileName, int playType);

		/**
		 * �T�E���h��~
		 *
		 * @param slotNum �X���b�g�ԍ�
		 */
		void StopSoundEX(int slotNum);

		/**
		 * �T�E���h�S��~
		 */
		void AllStop();

		/**
		 * �o�^�E�Đ���ԃ`�F�b�N
		 *
		 * @return �����i0�j�A���s�i-1�j
		 */
		int IsPlay();

	private:
		// �V���O���g��
		static SoundManager* m_sm;
		static bool m_destroyFlg; // Phoenix Singleton���p
		HWND m_hwnd;
		IDirectSound8* m_pDS8;

		//! �T�E���h�o�b�t�@�̈�(�v���� �T�E���h�|�[�g����BGM��SE���番������Ȃǂ̌���)
		IDirectSoundBuffer8* m_pSoundBuffer[D_SOUND_MAX];

		/**
		 * �R���X�g���N�^
		 */
		SoundManager();

		/**
		 * �Đ��\�X���b�g�擾
		 *
		 * @return �X���b�g�ԍ�
		 */
		int GetPlaySlot();

		/**
		 * �T�E���h�t�@�C���ǂݍ���
		 *
		 * @param fileName �t�@�C����
		 * @param playType �Đ��^�C�v
		 * @param port     �|�[�g
		 * @return �����i0�j�A���s�i-1�j
		 */
		int SoundFileOpen(std::string fileName, int playType, int port);

		/**
		 * �T�E���h�Đ�
		 *
		 * @param pWaveData wav�f�[�^
		 * @param waveSize  wav�T�C�Y
		 * @param wFmt      �t�H�[�}�b�g
		 * @param playType  �Đ��^�C�v
		 * @param port      �|�[�g
		 * @return �����i0�j�A���s�i-1�j
		 */
		int MyPlaySound(char* pWaveData, DWORD waveSize, WAVEFORMATEX wFmt, int playType, int port);

		/**
		 * �t�@�C������Wav�t�@�C���I�[�v��
		 *
		 * @param filePath     �t�@�C���p�X
		 * @param waveFormatEx wav�t�H�[�}�b�g
		 * @param ppData       �f�[�^
		 * @param dataSize     �f�[�^�T�C�Y
		 * @return �����i0�j�A���s�i-1�j
		 */
		int OpenWaveFromFile(std::string filePath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize);

		/**
		 * wav�ǂݍ���
		 *
		 * @param hMmio        �}���`���f�B�A�t�@�C�����o�͂̃n���h��
		 * @param waveFormatEx wav�t�H�[�}�b�g
		 * @param ppData       �f�[�^
		 * @param dataSize     �f�[�^�T�C�Y
		 * @return �����i0�j�A���s�i-1�j
		 */
		int OpenWave(HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize);
	};
}

#endif // UQ_LIB_SOUNDMANAGER_H

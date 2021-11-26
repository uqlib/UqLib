//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_FILEMANAGER_H
#define UQ_LIB_FILEMANAGER_H

#include <string>

//#include "Logger.h"

namespace uq_lib {

	class FileManager
	{
	public:

		/**
		 * �C���X�^���X�擾
		 *
		 * @return �C���X�^���X
		 */
		static FileManager* GetInstance() {
			if (!m_fm && m_destroyFlg == true) m_fm = new FileManager();
			return m_fm;
		}

		/**
		 * �j��
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_fm;
			m_fm = NULL;
		}

		/**
		 * �f�X�g���N�^
		 */
		virtual ~FileManager();

		/** Dat�t�@�C������t�@�C���ǂݍ���
		 *
		 * @param fileName    �t�@�C����
		 * @param buffer      �o�b�t�@
		 * @param size        �T�C�Y
		 * @return �����i0�j�A���s�i-1�j
		 */
		int LoadFileFromDatFile(std::string fileName, char** buffer, long* size);

	private:

		// �V���O���g��
		static FileManager* m_fm;
		static bool m_destroyFlg; // Phoenix Singleton���p

		char* DecodeXOR(char* data);

		/**
		 * �R���X�g���N�^
		 */
		FileManager();
	};
	}

#endif // UQ_LIB_FILEMANAGER_H

//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include "FileManager.h"

using namespace std;

namespace uq_lib {

	FileManager* FileManager::m_fm = NULL;
	bool FileManager::m_destroyFlg = true; // Phoenix Singleton���p

	FileManager::FileManager() {
	}

	FileManager::~FileManager() {
	}

	int FileManager::LoadFileFromDatFile(string fileName, char** buffer, long* size) {
		FILE* fp;
		if (fopen_s(&fp, fileName.c_str(), "rb") != 0) {
			//Logger::OutputWarn("�t�@�C���ǂݍ��݂Ɏ��s�B");
			return -1;
		}

		// �t�@�C���|�C���^fp���t�@�C���̐擪SEEK_SET����0�o�C�g�̒n�_�Ɉړ�������
		fseek(fp, 0, SEEK_END);
		*size = ftell(fp);
		rewind(fp);
		*buffer = (char*)malloc(sizeof(char) * (*size));
		if (*buffer == NULL) {
			//Logger::OutputWarn("�������m�ۂɎ��s�B");
			return -1;
		}
		fread(*buffer, 1, *size, fp);
		*buffer = DecodeXOR(*buffer);
		fclose(fp);

		return 0;
	}

	char* FileManager::DecodeXOR(char* data)
	{
		for (int i = 0; i < 256; i++)
		{
			if (data[i] == 0)
			{
				break;
			}
			data[i] ^= 0x99;
		}
		return data;
	}
}

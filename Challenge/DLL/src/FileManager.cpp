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
	bool FileManager::m_destroyFlg = true; // Phoenix Singleton回避用

	FileManager::FileManager() {
	}

	FileManager::~FileManager() {
	}

	int FileManager::LoadFileFromDatFile(string fileName, char** buffer, long* size) {
		FILE* fp;
		if (fopen_s(&fp, fileName.c_str(), "rb") != 0) {
			//Logger::OutputWarn("ファイル読み込みに失敗。");
			return -1;
		}

		// ファイルポインタfpをファイルの先頭SEEK_SETから0バイトの地点に移動させる
		fseek(fp, 0, SEEK_END);
		*size = ftell(fp);
		rewind(fp);
		*buffer = (char*)malloc(sizeof(char) * (*size));
		if (*buffer == NULL) {
			//Logger::OutputWarn("メモリ確保に失敗。");
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

//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_FILEMANAGER_H
#define UQ_LIB_FILEMANAGER_H

#include "Logger.h"

namespace uq_lib {

	class FileManager
	{
	public:

		/**
		 * インスタンス取得
		 *
		 * @return インスタンス
		 */
		static FileManager* GetInstance() {
			if (!m_fm && m_destroyFlg == true) m_fm = new FileManager();
			return m_fm;
		}

		/**
		 * 破棄
		 */
		static void Destroy() {
			m_destroyFlg = false;
			delete m_fm;
			m_fm = NULL;
		}

		/**
		 * デストラクタ
		 */
		virtual ~FileManager();

		/** Datファイルからファイル読み込み
		 *
		 * @param fileName    ファイル名
		 * @param buffer      バッファ
		 * @param size        サイズ
		 * @return 成功（0）、失敗（-1）
		 */
		int LoadFileFromDatFile(std::string fileName, char** buffer, long* size);

	private:

		// シングルトン
		static FileManager* m_fm;
		static bool m_destroyFlg; // Phoenix Singleton回避用

		char* DecodeXOR(char* data);

		/**
		 * コンストラクタ
		 */
		FileManager();
	};
	}

#endif // UQ_LIB_FILEMANAGER_H

//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_LOGGER_H
#define UQ_LIB_LOGGER_H

#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Constants.h"

namespace uq_lib {

	class Logger
	{
	public:

		/**
		 * ログレベル変更
		 *
		 * @param logLevel ログレベル
		 */
		static void ChangeLogLevel(int logLevel);

		/**
		 * Error判定
		 *
		 * @return 該当（true）、非該当（false）
		 */
		static bool JudgeError();

		/**
		 * Warn判定
		 *
		 * @return 該当（true）、非該当（false）
		 */
		static bool JudgeWarn();

		/**
		 * Info判定
		 *
		 * @return 該当（true）、非該当（false）
		 */
		static bool JudgeInfo();

		/**
		 * Debug判定
		 *
		 * @return 該当（true）、非該当（false）
		 */
		static bool JudgeDebug();

		/**
		 * Error出力
		 *
		 * @param msg メッセージ
		 */
		static void OutputError(std::string msg);

		/**
		 * Warn出力
		 *
		 * @param msg メッセージ
		 */
		static void OutputWarn(std::string msg);

		/**
		 * Info出力
		 *
		 * @param msg メッセージ
		 */
		static void OutputInfo(std::string msg);

		/**
		 * Debug出力
		 *
		 * @param msg メッセージ
		 */
		static void OutputDebug(std::string msg);

	private:
		static int m_logLevel;

		/**
		 * 出力
		 *
		 * @param logLevel ログレベル
		 * @param msg      メッセージ
		 */
		static void Output(int logLevel, std::string msg);

		/**
		 * 時間取得
		 *
		 * @return yyyy/mm/dd hh:mm:ss.sss
		 */
		static std::string GetTime();
	};
}

#endif // UQ_LIB_LOGGER_H

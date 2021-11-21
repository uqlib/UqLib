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
		 * ���O���x���ύX
		 *
		 * @param logLevel ���O���x��
		 */
		static void ChangeLogLevel(int logLevel);

		/**
		 * Error����
		 *
		 * @return �Y���itrue�j�A��Y���ifalse�j
		 */
		static bool JudgeError();

		/**
		 * Warn����
		 *
		 * @return �Y���itrue�j�A��Y���ifalse�j
		 */
		static bool JudgeWarn();

		/**
		 * Info����
		 *
		 * @return �Y���itrue�j�A��Y���ifalse�j
		 */
		static bool JudgeInfo();

		/**
		 * Debug����
		 *
		 * @return �Y���itrue�j�A��Y���ifalse�j
		 */
		static bool JudgeDebug();

		/**
		 * Error�o��
		 *
		 * @param msg ���b�Z�[�W
		 */
		static void OutputError(std::string msg);

		/**
		 * Warn�o��
		 *
		 * @param msg ���b�Z�[�W
		 */
		static void OutputWarn(std::string msg);

		/**
		 * Info�o��
		 *
		 * @param msg ���b�Z�[�W
		 */
		static void OutputInfo(std::string msg);

		/**
		 * Debug�o��
		 *
		 * @param msg ���b�Z�[�W
		 */
		static void OutputDebug(std::string msg);

	private:
		static int m_logLevel;

		/**
		 * �o��
		 *
		 * @param logLevel ���O���x��
		 * @param msg      ���b�Z�[�W
		 */
		static void Output(int logLevel, std::string msg);

		/**
		 * ���Ԏ擾
		 *
		 * @return yyyy/mm/dd hh:mm:ss.sss
		 */
		static std::string GetTime();
	};
}

#endif // UQ_LIB_LOGGER_H

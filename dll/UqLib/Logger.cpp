//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include "Logger.h"

using namespace std;

namespace uq_lib {

	int Logger::m_logLevel = Log::NONE_LV;

	void Logger::ChangeLogLevel(int logLevel) {
		m_logLevel = logLevel;
	}

	bool Logger::JudgeError() {
		bool ret = false;

		if (m_logLevel >= Log::ERROR_LV) {
			ret = true;
		}

		return ret;
	}

	bool Logger::JudgeWarn() {
		bool ret = false;

		if (m_logLevel >= Log::WARN_LV) {
			ret = true;
		}

		return ret;
	}

	bool Logger::JudgeInfo() {
		bool ret = false;

		if (m_logLevel >= Log::INFO_LV) {
			ret = true;
		}

		return ret;
	}

	bool Logger::JudgeDebug() {
		bool ret = false;

		if (m_logLevel >= Log::DEBUG_LV) {
			ret = true;
		}

		return ret;
	}

	void Logger::OutputError(string msg) {
		if (!JudgeError()) {
			return;
		}
		Output(Log::ERROR_LV, msg);
	}

	void Logger::OutputWarn(string msg) {
		if (!JudgeWarn()) {
			return;
		}
		Output(Log::WARN_LV, msg);
	}

	void Logger::OutputInfo(string msg) {
		if (!JudgeInfo()) {
			return;
		}
		Output(Log::INFO_LV, msg);
	}

	void Logger::OutputDebug(string msg) {
		if (!JudgeDebug()) {
			return;
		}
		Output(Log::DEBUG_LV, msg);
	}

	void Logger::Output(int logLevel, string msg) {

		string levelString;
		if (Log::DEBUG_LV == logLevel) {
			levelString = "DEBUG";
		}
		else if (Log::INFO_LV == logLevel) {
			levelString = "INFO";
		}
		else if (Log::WARN_LV == logLevel) {
			levelString = "WARN";
		}
		else if (Log::ERROR_LV == logLevel) {
			levelString = "ERROR";
		}
		else {
			return;
		}
		ofstream ofs(LOG_FILENAME, ios::app);

		ofs << GetTime() + " " + levelString + " " + msg << endl;

		ofs.close();
	}

	string Logger::GetTime() {

		SYSTEMTIME st;
		GetSystemTime(&st);

		std::ostringstream oss;
		oss << st.wYear
			<< "/"
			<< std::setfill('0')
			<< std::setw(2)
			<< st.wMonth
			<< "/"
			<< std::setfill('0')
			<< std::setw(2)
			<< st.wDay
			<< " "
			<< std::setfill('0')
			<< std::setw(2)
			<< st.wHour + 9
			<< ":"
			<< std::setfill('0')
			<< std::setw(2)
			<< st.wMinute
			<< ":"
			<< std::setfill('0')
			<< std::setw(2)
			<< st.wSecond
			<< "."
			<< std::setfill('0')
			<< std::setw(3)
			<< st.wMilliseconds
			<< std::flush;

		return oss.str();
	}
}

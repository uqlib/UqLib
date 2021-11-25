//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_CONSTANTS_H
#define UQ_LIB_CONSTANTS_H

// 解放処理用のマクロを定義
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = nullptr; } }

namespace uq_lib {

	static const int DONE = 0;
	static const int FAIL = -1;

	// Logger
	enum Log
	{
		NONE_LV = 0,
		ERROR_LV = 10,
		WARN_LV = 20,
		INFO_LV = 30,
		DEBUG_LV = 40
	};

	// マウス入力用定義
	enum Mouse
	{
		LEFT_CLICK = 101,
		RIGHT_CLICK = 102,
		NOT_CLICK = 0
	};

	// キー入力用定義
	enum Key
	{
		RETURN = 1,	// Enterキー
		ESC = 2,	// Escキー
		SPACE = 3,	// スペースキー
		LEFT = 4,	// 左キー
		UP = 5,		// 上キー
		RIGHT = 6,	// 右キー
		DOWN = 7,	// 下キー
		A = 8,		// Ａキー
		B = 9,		// Ｂキー
		C = 10,		// Ｃキー
		D = 11,		// Ｄキー
		E = 12,		// Ｅキー
		F = 13,		// Ｆキー
		G = 14,		// Ｇキー
		H = 15,		// Ｈキー
		I = 16,		// Ｉキー
		J = 17,		// Ｊキー
		K = 18,		// Ｋキー
		L = 19,		// Ｌキー
		M = 20,		// Ｍキー
		N = 21,		// Ｎキー
		O = 22,		// Ｏキー
		P = 23,		// Ｐキー
		Q = 24,		// Ｑキー
		R = 25,		// Ｒキー
		S = 26,		// Ｓキー
		T = 27,		// Ｔキー
		U = 28,		// Ｕキー
		V = 29,		// Ｖキー
		W = 30,		// Ｗキー
		X = 31,		// Ｘキー
		Y = 32,		// Ｙキー
		Z = 33		// Ｚキー
	};

	// ファイル名
	static const char* LOG_FILENAME = "app.log";

	// サウンド用定義
	static const int D_PLAY_SOUND_BGM = 1;
	static const int D_PLAY_SOUND_SE = 2;
	static const int D_PLAY_SOUND_MAX = 3;
	static const int D_SOUND_MAX = 5;

	// FONT
	static const int DEFAULT_FONT_SIZE = 24;

	// SCREEN
	static const int DEFAULT_WIDTH = 1280;
	static const int DEFAULT_HEIGHT = 720;
}

#endif // UQ_LIB_CONSTANTS_H

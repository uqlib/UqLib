//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_CONSTANTS_H
#define UQ_LIB_CONSTANTS_H

// ��������p�̃}�N�����`
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

	// �}�E�X���͗p��`
	enum Mouse
	{
		LEFT_CLICK = 101,
		RIGHT_CLICK = 102,
		NOT_CLICK = 0
	};

	// �L�[���͗p��`
	enum Key
	{
		RETURN = 1,	// Enter�L�[
		ESC = 2,	// Esc�L�[
		SPACE = 3,	// �X�y�[�X�L�[
		LEFT = 4,	// ���L�[
		UP = 5,		// ��L�[
		RIGHT = 6,	// �E�L�[
		DOWN = 7,	// ���L�[
		A = 8,		// �`�L�[
		B = 9,		// �a�L�[
		C = 10,		// �b�L�[
		D = 11,		// �c�L�[
		E = 12,		// �d�L�[
		F = 13,		// �e�L�[
		G = 14,		// �f�L�[
		H = 15,		// �g�L�[
		I = 16,		// �h�L�[
		J = 17,		// �i�L�[
		K = 18,		// �j�L�[
		L = 19,		// �k�L�[
		M = 20,		// �l�L�[
		N = 21,		// �m�L�[
		O = 22,		// �n�L�[
		P = 23,		// �o�L�[
		Q = 24,		// �p�L�[
		R = 25,		// �q�L�[
		S = 26,		// �r�L�[
		T = 27,		// �s�L�[
		U = 28,		// �t�L�[
		V = 29,		// �u�L�[
		W = 30,		// �v�L�[
		X = 31,		// �w�L�[
		Y = 32,		// �x�L�[
		Z = 33		// �y�L�[
	};

	// �t�@�C����
	static const char* LOG_FILENAME = "app.log";

	// �T�E���h�p��`
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

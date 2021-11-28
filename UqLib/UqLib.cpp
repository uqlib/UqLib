//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include <stdio.h>
#include "UqLib.h" //先ほど定義したヘッダファイル
#include "DirectXManager.h"
#include "SoundManager.h"
#include "GraphicsManager.h"

using namespace std;
using namespace uq_lib;

SystemClass* g_pSystemClass;

// デフォルト設定はADVゲーム向けサイズ
int g_screenWidth = DEFAULT_WIDTH;
int g_screenHeight = DEFAULT_HEIGHT;

wstring StringToWString(string oString) {
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str()
		, -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2
		, iBufferSize);

	// stringの生成
	wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	// 変換結果を返す
	return(oRet);
}

int UqLibInit(const char* title) {
	Logger::ChangeLogLevel(Log::DEBUG_LV);
	locale::global(locale("")); // wstringのログ出力に必要

	g_pSystemClass = new SystemClass();

	return g_pSystemClass->Initialize(std::string(title), g_screenWidth, g_screenHeight);
}

int UqLibEnd() {
	SoundManager::GetInstance()->AllStop(); // サウンド全停止と破棄
	SoundManager::GetInstance()->Destroy();
	GraphicsManager::GetInstance()->ReleaseAll();
	GraphicsManager::GetInstance()->Destroy();

	delete g_pSystemClass;
	g_pSystemClass = 0;
	return 0;
}

int BeginDrawing() {
	if (UpdateWindowMessage() == -1) {
		return -1;
	}
	return GraphicsManager::GetInstance()->BeginDrawing();
}

int EndDrawing() {
	return GraphicsManager::GetInstance()->EndDrawing();
}

int CreateFontContener(int height, const char* fontName) {
	return GraphicsManager::GetInstance()->CreateFontContener(height, StringToWString(fontName));
}

int CreateTextureFromFile(const char* fileName) {
	return GraphicsManager::GetInstance()->CreateTextureFromFile(StringToWString(fileName));
}

int CreateTextureFromDatFile(const char* fileName) {
	return GraphicsManager::GetInstance()->CreateTextureFromDatFile(std::string(fileName));
}

int DrawTexture(int x, int y, int graphicId) {
	if (graphicId == -1) {
		return -1;
	}
	return GraphicsManager::GetInstance()->DrawTexture(graphicId, x, y);
}

int DrawTextureAlpha(int x, int y, int graphicId, float opacity) {
	if (graphicId == -1) {
		return -1;
	}
	return GraphicsManager::GetInstance()->DrawTexture(graphicId, x, y, opacity);
}

int DrawTextureClip(int x, int y, int graphicId, int cx, int cy, int cw, int ch) {
	if (graphicId == -1) {
		return -1;
	}
	return GraphicsManager::GetInstance()->DrawTexture(graphicId, x, y, cx, cy, cw, ch);
}

int DrawTextureClipAlpha(int x, int y, int graphicId, int cx, int cy, int cw, int ch, float opacity) {
	if (graphicId == -1) {
		return -1;
	}
	return GraphicsManager::GetInstance()->DrawTexture(graphicId, x, y, cx, cy, cw, ch, opacity);
}

int DrawString(int x, int y, const char* text, int fontId, UINT32 hexColorCode) {
	return GraphicsManager::GetInstance()->DrawString(x, y, std::string(text), fontId, hexColorCode);
}

int DrawStringAlpha(int x, int y, const char* text, int fontId, UINT32 hexColorCode, float opacity) {
	return GraphicsManager::GetInstance()->DrawString(x, y, std::string(text), fontId, hexColorCode, opacity);
}

int UpdateWindowMessage() {
	if (g_pSystemClass->UpdateWindow() == -1) {
		return -1;
	}
	if (g_pSystemClass->IsQuitMessage() == -1) {
		return -1;
	}
	return 0;
}

int CheckPressedKey(int keyCode) {
	return g_pSystemClass->CheckPressedKey(keyCode);
}

int CheckPressKey(int keyCode) {
	return g_pSystemClass->CheckPressKey(keyCode);
}

int PlaySoundFromFile(const char* fileName, int playType) {
	return SoundManager::GetInstance()->PlaySoundFromFile(std::string(fileName), playType);
}

int CheckSoundPlay() {
	return SoundManager::GetInstance()->IsPlay();
}

void ApplicationQuit() {
	g_pSystemClass->AppQuit();
}

int SetWindowTitle(const char* title) {
	return g_pSystemClass->SetWindowTitle(std::string(title));
}

int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width) {
	return GraphicsManager::GetInstance()->DrawLine(x, y, ax, ay, hexColorCode, width);
}

int DrawLineAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float width, float opacity) {
	return GraphicsManager::GetInstance()->DrawLine(x, y, ax, ay, hexColorCode, width, opacity);
}

int DrawSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth) {
	return GraphicsManager::GetInstance()->DrawSquare(x, y, ax, ay, hexColorCode, strokeWidth);
}

int DrawSquareAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth, float opacity) {
	return GraphicsManager::GetInstance()->DrawSquare(x, y, ax, ay, hexColorCode, strokeWidth, opacity);
}

int FillSquare(int x, int y, int ax, int ay, UINT32 hexColorCode) {
	return GraphicsManager::GetInstance()->FillSquare(x, y, ax, ay, hexColorCode);
}

int FillSquareAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float opacity) {
	return GraphicsManager::GetInstance()->FillSquare(x, y, ax, ay, hexColorCode, opacity);
}

int DrawRoundedSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth, float radius) {
	return GraphicsManager::GetInstance()->DrawRoundedSquare(x, y, ax, ay, hexColorCode, strokeWidth, radius);
}

int DrawRoundedSquareAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float strokeWidth, float radius, float opacity) {
	return GraphicsManager::GetInstance()->DrawRoundedSquare(x, y, ax, ay, hexColorCode, strokeWidth, radius, opacity);
}

int FillRoundedSquare(int x, int y, int ax, int ay, UINT32 hexColorCode, float radius) {
	return GraphicsManager::GetInstance()->FillRoundedSquare(x, y, ax, ay, hexColorCode, radius);
}

int FillRoundedSquareAlpha(int x, int y, int ax, int ay, UINT32 hexColorCode, float radius, float opacity) {
	return GraphicsManager::GetInstance()->FillRoundedSquare(x, y, ax, ay, hexColorCode, radius, opacity);
}

int DrawEllipse(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth) {
	return GraphicsManager::GetInstance()->DrawEllipse(x, y, width, height, hexColorCode, strokeWidth);
}

int DrawEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float strokeWidth, float opacity) {
	return GraphicsManager::GetInstance()->DrawEllipse(x, y, width, height, hexColorCode, strokeWidth, opacity);
}

int FillEllipse(int x, int y, int width, int height, UINT32 hexColorCode) {
	return GraphicsManager::GetInstance()->FillEllipse(x, y, width, height, hexColorCode);
}

int FillEllipseAlpha(int x, int y, int width, int height, UINT32 hexColorCode, float opacity) {
	return GraphicsManager::GetInstance()->FillEllipse(x, y, width, height, hexColorCode, opacity);
}

void GetLeftClickPoint(int* x, int* y) {
	g_pSystemClass->GetLeftClickPoint(x, y);
}

int WaitProcessing(int waitTime) {
	DWORD beginTime; // 一つ前に状態を取得した時間
	beginTime = timeGetTime();
	while (true) {
		DWORD now = timeGetTime();
		DWORD elapsedMilliseconds = now - beginTime;
		if (elapsedMilliseconds > (DWORD)waitTime) {
			break;
		}
		UpdateWindowMessage();
	}
	return 0;
}

int InitScreenSize(int screenWidth, int screenHeight) {
	g_screenWidth = screenWidth;
	g_screenHeight = screenHeight;
	return 0;
}

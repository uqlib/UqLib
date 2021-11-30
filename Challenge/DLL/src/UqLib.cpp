#include <stdio.h>
#include "UqLib.h"
#include "GraphicsManager.h"

using namespace std;
using namespace uq_lib;

SystemClass* g_pSystemClass;

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

	return g_pSystemClass->Initialize(std::string(title), 1270, 720);
}

int UqLibEnd() {
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

int UpdateWindowMessage() {
	if (g_pSystemClass->UpdateWindow() == -1) {
		return -1;
	}
	if (g_pSystemClass->IsQuitMessage() == -1) {
		return -1;
	}
	return 0;
}

int CreateFontContener(int height, const char* fontName) {
	return GraphicsManager::GetInstance()->CreateFontContener(height, StringToWString(fontName));
}

int CreateTextureFromFile(const char* fileName) {
	return GraphicsManager::GetInstance()->CreateTextureFromFile(StringToWString(fileName), fileName);
}

int CreateTextureFromDatFile(const char* fileName) {
	return GraphicsManager::GetInstance()->CreateTextureFromDatFile(std::string(fileName));
}

int DrawTexture(int x, int y, int graphicId) {
	Logger::OutputInfo("### DrawTexture 1");
	if (graphicId == -1) {
		return -1;
	}
	Logger::OutputInfo("### DrawTexture 2");
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

int CheckPressedKey(int keyCode) {
	return g_pSystemClass->CheckPressedKey(keyCode);
}

int DrawLine(int x, int y, int ax, int ay, UINT32 hexColorCode, float width) {
	return GraphicsManager::GetInstance()->DrawLine(x, y, ax, ay, hexColorCode, width);
}

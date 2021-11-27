#ifndef UQ_LIB_H
#define UQ_LIB_H

#include "SystemClass.h"
#include "Logger.h"
#include "Constants.h"

// DirectX11系の静的ライブラリをリンク
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")//テキスト表示用
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

extern "C" __declspec (dllexport) int UqLibInit(const char* title);

extern "C" __declspec (dllexport) int UqLibEnd();

extern "C" __declspec (dllexport) int BeginDrawing();

extern "C" __declspec (dllexport) int EndDrawing();

extern "C" __declspec (dllexport) int UpdateWindowMessage();

extern "C" __declspec (dllexport) int CreateFontContener(int height, const char* fontName);

extern "C" __declspec (dllexport) int DrawString(int x, int y, const char* text, int fontId, UINT32 hexColorCode);

#endif

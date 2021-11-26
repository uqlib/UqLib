#ifndef UQ_LIB_H
#define UQ_LIB_H

#include "SystemClass.h"
#include "Logger.h"
#include "Constants.h"

extern "C" __declspec (dllexport) int UqLibInit(const char* title);

extern "C" __declspec (dllexport) int UqLibEnd();

extern "C" __declspec (dllexport) int BeginDrawing();

extern "C" __declspec (dllexport) int EndDrawing();

extern "C" __declspec (dllexport) int UpdateWindowMessage();

#endif

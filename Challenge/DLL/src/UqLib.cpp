#include <stdio.h>
#include "UqLib.h"

using namespace std;
using namespace uq_lib;

SystemClass* g_pSystemClass;

int UqLibInit(const char* title) {
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
	return 0;
}

int EndDrawing() {
	return 0;
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

#include <stdio.h>
#include "UqLib.h"

using namespace std;
using namespace uq_lib;

SystemClass* g_pSystemClass;

int UqLibInit(const char* title) {
	g_pSystemClass = new SystemClass();

	return g_pSystemClass->Initialize(std::string(title), 1270, 720);
}
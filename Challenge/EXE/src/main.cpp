#include <windows.h>
#include <stdio.h>

using namespace std;

//__declspec(dllimport) int UqLibInit(int, int);

typedef int(*UQ_LIB_INIT)(const char* title);
typedef int(*UQ_LIB_END)();
typedef int(*BEGIN_DRAWING)();
typedef int(*END_DRAWING)();
//typedef int(*INIT_SCREEN_SIZE)(int screenWidth, int screenHeight);
//typedef int(*UPDATE_WINDOW_MESSAGE)();
//typedef int(*BEGIN_DRAWING)();
//typedef int(*CREATE_TEXTURE_FROM_FILE)(const char* filename);
//typedef int(*DRAW_TEXTURE)(int x, int y, int graphicId);

int main() {
	HINSTANCE hDllInstance = ::LoadLibrary("UqLib.dll");//DLL‚ðŽw’è
	if (NULL == hDllInstance) {
		return 1;
	}
	UQ_LIB_INIT UqLibInit = (UQ_LIB_INIT)GetProcAddress(hDllInstance, "UqLibInit");
	UQ_LIB_END UqLibEnd = (UQ_LIB_END)GetProcAddress(hDllInstance, "UqLibEnd");
	BEGIN_DRAWING BeginDrawing = (BEGIN_DRAWING)GetProcAddress(hDllInstance, "BeginDrawing");
	END_DRAWING EndDrawing = (END_DRAWING)GetProcAddress(hDllInstance, "EndDrawing");
	//INIT_SCREEN_SIZE InitScreenSize = (INIT_SCREEN_SIZE)GetProcAddress(hDllInstance, "InitScreenSize");
	//UPDATE_WINDOW_MESSAGE UpdateWindowMessage = (UPDATE_WINDOW_MESSAGE)GetProcAddress(hDllInstance, "UpdateWindowMessage");
	//BEGIN_DRAWING BeginDrawing = (BEGIN_DRAWING)GetProcAddress(hDllInstance, "BeginDrawing");
	//CREATE_TEXTURE_FROM_FILE CreateTextureFromFile = (CREATE_TEXTURE_FROM_FILE)GetProcAddress(hDllInstance, "CreateTextureFromFile");
	//DRAW_TEXTURE DrawTexture = (DRAW_TEXTURE)GetProcAddress(hDllInstance, "DrawTexture");

	int c;
	c = UqLibInit("test‚ ");
	printf("%d", c);
	
	while (BeginDrawing() == 0) {
		EndDrawing();
	}

	UqLibEnd();

	return 0;
}
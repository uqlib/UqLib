#include <windows.h>
#include <string>

using namespace std;

typedef int(*INIT_SCREEN_SIZE)(int width, int height);
typedef int(*UQ_LIB_INIT)(const char* title);
typedef int(*UPDATE_WINDOW_MESSAGE)();
typedef int(*BEGIN_DRAWING)();
typedef int(*END_DRAWING)();
typedef int(*UQ_LIB_END)();
typedef int(*CREATE_TEXTURE_FROM_FILE)(const char* filename);
typedef int(*DRAW_TEXTURE)(int x, int y, int graphicId);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HINSTANCE hDllInstance = ::LoadLibrary("UqLib.dll");//DLLを指定
	if (NULL == hDllInstance) {
		return 1;
	}
	INIT_SCREEN_SIZE InitScreenSize = (INIT_SCREEN_SIZE)GetProcAddress(hDllInstance, "InitScreenSize");
	UQ_LIB_INIT UqLibInit = (UQ_LIB_INIT)GetProcAddress(hDllInstance, "UqLibInit");
	UPDATE_WINDOW_MESSAGE UpdateWindowMessage = (UPDATE_WINDOW_MESSAGE)GetProcAddress(hDllInstance, "UpdateWindowMessage");
	BEGIN_DRAWING BeginDrawing = (BEGIN_DRAWING)GetProcAddress(hDllInstance, "BeginDrawing");
	END_DRAWING EndDrawing = (END_DRAWING)GetProcAddress(hDllInstance, "EndDrawing");
	UQ_LIB_END UqLibEnd = (UQ_LIB_END)GetProcAddress(hDllInstance, "UqLibEnd");
	CREATE_TEXTURE_FROM_FILE CreateTextureFromFile = (CREATE_TEXTURE_FROM_FILE)GetProcAddress(hDllInstance, "CreateTextureFromFile");
	DRAW_TEXTURE DrawTexture = (DRAW_TEXTURE)GetProcAddress(hDllInstance, "DrawTexture");

	InitScreenSize(1280, 960);

	if (UqLibInit("サンプル") == -1) {
		return -1;
	}

	int bmp1 = 0;
	bmp1 = CreateTextureFromFile("test.png");

	while (UpdateWindowMessage() == 0 && BeginDrawing() == 0) {
		DrawTexture(0, 0, bmp1);
		EndDrawing();
	}

	UqLibEnd();

	return 0;					// ソフトの終了 
}

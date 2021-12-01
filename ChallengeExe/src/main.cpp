#include <windows.h>
#include <stdio.h>

using namespace std;

typedef int(*UQ_LIB_INIT)(const char* title);
typedef int(*UQ_LIB_END)();
typedef int(*BEGIN_DRAWING)();
typedef int(*END_DRAWING)();

typedef int(*CREATE_FONT_CONTENER)(int height, const char* fontName);
typedef int(*CREATE_TEXTURE_FROM_FILE)(const char * filename);
typedef int(*DRAW_TEXTURE)(int x, int y, int graphicId);
typedef int(*DRAW_STRING)(int x, int y, const char* text, int fontId, UINT32 hexColorCode);
typedef int(*DRAW_LINE)(int x, int y, int ax, int ay, UINT32 hexColorCode, float width);

int main() {
	HINSTANCE hDllInstance = ::LoadLibrary("UqLib.dll");//DLL‚ðŽw’è
	if (NULL == hDllInstance) {
		return 1;
	}
	UQ_LIB_INIT UqLibInit = (UQ_LIB_INIT)GetProcAddress(hDllInstance, "UqLibInit");
	UQ_LIB_END UqLibEnd = (UQ_LIB_END)GetProcAddress(hDllInstance, "UqLibEnd");
	BEGIN_DRAWING BeginDrawing = (BEGIN_DRAWING)GetProcAddress(hDllInstance, "BeginDrawing");
	END_DRAWING EndDrawing = (END_DRAWING)GetProcAddress(hDllInstance, "EndDrawing");
	
	CREATE_FONT_CONTENER CreateFontContener = (CREATE_FONT_CONTENER)GetProcAddress(hDllInstance, "CreateFontContener");
	CREATE_TEXTURE_FROM_FILE CreateTextureFromFile = (CREATE_TEXTURE_FROM_FILE)GetProcAddress(hDllInstance, "CreateTextureFromFile");
	DRAW_TEXTURE DrawTexture = (DRAW_TEXTURE)GetProcAddress(hDllInstance, "DrawTexture");
	DRAW_STRING DrawString = (DRAW_STRING)GetProcAddress(hDllInstance, "DrawString");
	DRAW_LINE DrawLine = (DRAW_LINE)GetProcAddress(hDllInstance, "DrawLine");

	int c;
	c = UqLibInit("test‚ ");
	printf("c: %d\n", c);
	
	int font1 = CreateFontContener(30, "‚l‚r ƒSƒVƒbƒN");
	
	printf("font1: %d\n", font1);
	
	int bmp1 = CreateTextureFromFile("test.png");

	while (BeginDrawing() == 0) {
		DrawString(10, 10, "AAA", font1, 0x00FF00);
		DrawLine(250, 50, 300, 100, 0x0000FF, 5);
		DrawTexture(30, 200, bmp1);
		EndDrawing();
	}

	UqLibEnd();

	return 0;
}
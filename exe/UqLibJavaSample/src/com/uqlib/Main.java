package com.uqlib;


import com.sun.jna.Library;
import com.sun.jna.Native;

interface UqLib extends Library {
	  // loadLibrary
	  @SuppressWarnings("deprecation")
	  UqLib INSTANCE = (UqLib) Native.loadLibrary("UqLib.dll", UqLib.class);

	  int UqLibInit(String title);
	  int UqLibEnd();
	  int UpdateWindowMessage();
	  void ApplicationQuit();

	  //int InitScreenSize(int width, int height);
	  int CreateTextureFromFile(String fileName);
	  int BeginDrawing();
	  int EndDrawing();
	  int DrawTexture(int x, int y, int graphicId);
}

public class Main {

	public static void main(String[] args) {

        UqLib uqLib = UqLib.INSTANCE;
        //uqLib.InitScreenSize(1280, 960);

		if (uqLib.UqLibInit("sample game") == -1)
		{
		    return;
		}

		int bmp1 = 0;
		bmp1 = uqLib.CreateTextureFromFile("test.png");

		while(uqLib.BeginDrawing() == 0) {
			uqLib.DrawTexture(0, 0, bmp1);
			uqLib.EndDrawing();
		}
		uqLib.UqLibEnd();
	}
}

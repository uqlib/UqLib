//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
using System;
using System.Runtime.InteropServices;

namespace UqLibCsharpSample
{
    class GameMain
    {
        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int UqLibInit(string lpPathName);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int UqLibEnd();

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CreateTextureFromFile(string filename);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CreateTextureFromZipFile(string zipFilename, string filename, string password);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CreateFontContener(int height, string fontName);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawTexture(int x, int y, int graphicId);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawTextureClip(int x, int y, int graphicId, int sx, int sy, int sw, int sh);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawString(int x, int y, string text, int fontId, uint hexColorCode);
        
        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CheckPressedKey(int keyCode);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CheckPressKey(int keyCode);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int BeginDrawing();

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int EndDrawing();

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int PlaySoundFromFile(string fileName, int playType);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int CheckSoundPlay();

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void ApplicationQuit();

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int SetWindowTitle(string title);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawLine(int x, int y, int ax, int ay, uint hexColorCode, int width);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawSquareAlpha(int x, int y, int sx, int sy, uint hexColorCode, float strokeWidth, float opacity);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawRoundedSquareAlpha(int x, int y, int sx, int sy, uint hexColorCode, float strokeWidth, float radius, float opacity);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int DrawEllipseAlpha(int x, int y, int width, int height, uint hexColorCode, float strokeWidth, float opacity);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void GetLeftClickPoint(IntPtr x, IntPtr y);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int WaitProcessing(int waitTime);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int InitScreenSize(int width, int height);

        [DllImport("UqLib.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void CreateTextureFromDatFile(string fileName);

        static void Main(string[] args)
        {
            InitScreenSize(1280, 960);

            // UqLib初期化処理
            if (UqLibInit("サンプルゲーム") == -1)
            {
                // エラーが起きたら直ちに終了
                return;
            }

            CreateTextureFromDatFile("aaa.dat");

            SetWindowTitle("TEST");

            int n = 0;

            int bmp1 = 0;
            //bmp1 = CreateTextureFromFile("test.png");
            //bmp1 = CreateTextureFromZipFile("data/test.zip", "test/mu_standing1.bmp", "");

            int font1 = CreateFontContener(30, "ＭＳ ゴシック");

            while (BeginDrawing() == 0)
            {
                // サウンド再生状態をここでチェック(のちにスレッド化
                CheckSoundPlay();

                // RETURN
                if (CheckPressedKey(1) != 0)
                {
                    PlaySoundFromFile("sample_se.wav", 2);
                    DrawString(10, 10 + n, "ENTER", font1, 0x00FF00);
                    n += 20;
                }
                else if (CheckPressedKey((int)Constants.Mouse.LEFT_CLICK) != 0)
                {
                    DrawString(10, 10 + n, "LEFT", font1, 0x00FF00);
                    n += 20;
                }
                else if (CheckPressedKey((int)Constants.Mouse.RIGHT_CLICK) != 0)
                {
                    DrawString(10, 10 + n, "RIGHT", font1, 0x00FF00);
                    n += 20;
                }
                else if (CheckPressedKey((int)Constants.Key.ESC) != 0)
                {
                    ApplicationQuit();
                }

                IntPtr bufferX = new IntPtr();
                bufferX = Marshal.AllocHGlobal(2); //2バイトのメモリ確保
                IntPtr bufferY = new IntPtr();
                bufferY = Marshal.AllocHGlobal(2); //2バイトのメモリ確保
                GetLeftClickPoint(bufferX, bufferY);
                int x = Marshal.ReadInt32(bufferX);
                int y = Marshal.ReadInt32(bufferY);
                Marshal.FreeHGlobal(bufferX);
                Marshal.FreeHGlobal(bufferY);
                DrawString(110, 100, "ロード", font1, 0x00FF00);
                DrawTexture(0, 0, 99);

                DrawLine(0, 100, 20, 300, 0xFFFFFF, 5);
                DrawSquareAlpha(100, 200, 100, 100, 0xFFFFFF, 10, 1.0f);
                DrawRoundedSquareAlpha(20, 100, 100, 100, 0xFFFFFF, 10, 10.0f, 0.2f);
                DrawRoundedSquareAlpha(20, 150, 100, 100, 0xFFFFFF, 10, 2.0f, 0.2f);
                DrawSquareAlpha(100, 600, 100, 100, 0xFFFFFF, 5, 1.0f);
                DrawEllipseAlpha(300, 200, 100, 100, 0xFFFFFF, 1, 0.2f);
                DrawEllipseAlpha(300, 400, 100, 100, 0xFFFFFF, 0, 0.2f);
                DrawEllipseAlpha(300, 600, 100, 100, 0xFFFFFF, 5, 0.2f);

                // 描画終了（バックバッファをメインバッファに転送）
                EndDrawing();
                WaitProcessing(100);
            }
            UqLibEnd();

            return; 
        }
    }
}
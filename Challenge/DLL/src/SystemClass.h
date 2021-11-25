//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#ifndef UQ_LIB_SYSTEMCLASS_H
#define UQ_LIB_SYSTEMCLASS_H

#include <windows.h>
#include <string>
#include <time.h>
#include <map>
#include "Constants.h"

namespace uq_lib {

	class SystemClass
	{
	public:

		/**
		 * 初期化
		 *
		 * @param title        タイトル
		 * @param screenWidth  画面の幅
		 * @param screenHeight 画面の高さ
		 * @return 成功（0）、失敗（-1）
		 */
		int Initialize(std::string title, int screenWidth, int screenHeight);

		/**
		 * ウィンドウ更新
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int UpdateWindow();

		/**
		 * メッセージハンドラ
		 *
		 * @param hWnd ウィンドウハンドル
		 * @param message メッセージ
		 * @param wParam wパラメータ
		 * @param lParam lパラメータ
		 * @return メッセージ処理の結果
		 */
		static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		/**
		 * アプリ終了
		 */
		void AppQuit();

		/**
		 * 終了メッセージ
		 *
		 * @return 終了通知が来ていない（0）、終了通知が来ている（-1）
		 */
		int IsQuitMessage();

		/**
		 * ウィンドウタイトル設定
		 *
		 * @param title タイトル
		 * @return 成功（0）、失敗（-1）
		 */
		int SetWindowTitle(std::string title);

		/**
		 * 左クリックポイント取得
		 *
		 * @param x X座標
		 * @param y Y座標
		 */
		void GetLeftClickPoint(int* x, int* y);

		/**
		 * キーを押したか確認
		 *
		 * @param keyCode キーコード
		 * @return 0：押していない、1：押した
		 */
		int CheckPressedKey(int keyCode);

		/**
		 * キーを押しているか確認
		 *
		 * @param keyCode キーコード
		 * @return 0：押していない、1：押している
		 */
		int CheckPressKey(int keyCode);

	private:

		static int m_message;
		static POINT m_clickPoint;
		LPCSTR m_applicationName = NULL;
		HINSTANCE m_hinstance;
		HWND m_hwnd;
		bool m_isQuitMessage; // 終了通知が来ているか？
		std::map<int, int> m_keyInputs;
		DWORD m_time;

		/**
		 * ウィンドウ初期化
		 *
		 * @param title タイトル
		 * @param screenWidth 画面の幅
		 * @param screenHeight 画面の高さ
		 * @return 成功（0）、失敗（-1）
		 */
		int InitializeWindow(std::string title, int screenWidth, int screenHeight);

		/**
		 * ウィンドウメッセージ更新
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int UpdateWindowMessage();

		/**
		 * キーボードの状態更新
		 *
		 * @return 成功（0）、失敗（-1）
		 */
		int UpdateKeyboardState();

		/**
		 * キー更新
		 *
		 * @param keyStates キー状態
		 * @param sysKey    システムキー
		 * @param myKey     マイキー
		 * @return 成功（0）、失敗（-1）
		 */
		int UpdateKey(BYTE* keyStates, int sysKey, int myKey);

		/**
		 * キー更新
		 *
		 * @param chara  文字
		 * @param sysKey システムキー
		 * @param myKey  マイキー
		 * @return 成功（0）、失敗（-1）
		 */
		int UpdateKey2(char chara, int sysKey, int myKey);

		/**
		 * クライアントのウィンドウサイズ変更
		 *
		 * @param hWnd   ウィンドウハンドル
		 * @param width  幅
		 * @param height 高さ
		 * @return 成功（0）、失敗（-1）
		 */
		int WindowResizeByClient(HWND hWnd, int width, int height);
	};

	/**
	 * ウィンドウプロシージャ
	 *
	 * @param hWnd     ウィンドウハンドル
	 * @param uMessage メッセージ
	 * @param wParam   wパラメータ
	 * @param lParam   lパラメータ
	 * @return 成功（0）、失敗（-1）
	 */
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
}

#endif // UQ_LIB_SYSTEMCLASS_H

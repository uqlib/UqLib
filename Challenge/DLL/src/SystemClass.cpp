//-----------------------------------------------------
// Copyright (c) UqLib. All rights reserved.
// Licensed under the MIT License.
// http://uqlib.com
//-----------------------------------------------------
#include "SystemClass.h"

using namespace std;

namespace uq_lib {

	int SystemClass::m_message = 0;
	POINT SystemClass::m_clickPoint = { 0, 0 };

	int SystemClass::Initialize(string title, int screenWidth, int screenHeight) {
		m_message = 0;

		// フルスクリーンかウインドウかを設定
		bool fullScrean = false;

		if (fullScrean) {
			screenWidth = GetSystemMetrics(SM_CXSCREEN);
			screenHeight = GetSystemMetrics(SM_CYSCREEN);
		}

		InitializeWindow(title, screenWidth, screenHeight);
		WindowResizeByClient(m_hwnd, screenWidth, screenHeight);

		return 0;
	}

	int SystemClass::UpdateWindow() {
		UpdateWindowMessage();
		if (UpdateKeyboardState() == -1) {
			return -1;
		}
		return 0;
	}

	LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

		switch (message) {
		case WM_LBUTTONDOWN:
			m_message = Mouse::LEFT_CLICK;
			m_clickPoint.x = LOWORD(lParam);
			m_clickPoint.y = HIWORD(lParam);
			break;
		case WM_RBUTTONDOWN:
			m_message = Mouse::RIGHT_CLICK;
			break;
		default:
			m_message = Mouse::NOT_CLICK;
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return 0;
	}

	void SystemClass::AppQuit() {
		PostQuitMessage(0);
	}

	int SystemClass::IsQuitMessage() {
		if (m_isQuitMessage) {
			return -1;
		}
		return 0;
	}

	int SystemClass::SetWindowTitle(string title) {
		SetWindowText(m_hwnd, title.c_str());
		return true;
	}

	void SystemClass::GetLeftClickPoint(int* x, int* y) {
		*x = SystemClass::m_clickPoint.x;
		*y = SystemClass::m_clickPoint.y;
	}

	int SystemClass::CheckPressedKey(int keyCode) {
		if (keyCode == Mouse::LEFT_CLICK) {
			if (m_message == Mouse::LEFT_CLICK) {
				m_message = 0;
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (keyCode == Mouse::RIGHT_CLICK) {
			if (m_message == Mouse::RIGHT_CLICK) {
				m_message = 0;
				return 1;
			}
			else {
				return 0;
			}
		}

		//0:ボタン離した時
		//1:ボタン押した時(CheckPushKey前)
		//2:ボタン押した時(CheckPushKey後)
		//3:ボタン離した時(CheckPushKey前)
		int keyInput = m_keyInputs[keyCode];
		if (keyInput == 0) {
			// 設定なし
			return 0;
		}
		else if (keyInput == 1) {
			m_keyInputs[keyCode] = 2;
			return 1;
		}
		else if (keyInput == 2) {
			return 0;
		}
		else if (keyInput == 3) {
			m_keyInputs[keyCode] = 0;
			return 1;
		}

		return 0;
	}

	int SystemClass::CheckPressKey(int keyCode) {
		//0:ボタン離した時
		//1:ボタン押した時(CheckPushKey前)
		//2:ボタン押した時(CheckPressKey後)
		//3:ボタン離した時(CheckPushKey前)
		int keyInput = m_keyInputs[keyCode];
		if (keyInput == 0) {
			// 設定なし
			return 0;
		}
		else if (keyInput == 1) {
			return 1;
		}
		else if (keyInput == 2) {
			return 1;
		}
		else if (keyInput == 3) {
			m_keyInputs[keyCode] = 0;
			return 0;
		}

		return 0;
	}

	int SystemClass::InitializeWindow(string title, int screenWidth, int screenHeight) {
		printf("SystemClass - InitializeWindow\n");
		WNDCLASSEX  wc;
		char modname[] = "uqlib.dll"; // DLL名
		m_hinstance = GetModuleHandle(NULL);
		m_applicationName = title.c_str();
		ZeroMemory(&wc, sizeof(wc));
		wc.style = 0;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_applicationName;
		wc.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&wc);
		m_hwnd = CreateWindowEx(
			WS_EX_APPWINDOW
			, m_applicationName
			, m_applicationName
			, WS_OVERLAPPEDWINDOW | WS_VISIBLE
			, CW_USEDEFAULT
			, CW_USEDEFAULT
			, screenWidth
			, screenHeight
			, HWND_DESKTOP
			, NULL
			, m_hinstance
			, NULL
		);
		return 0;
	}

	int SystemClass::UpdateWindowMessage() {
		MSG msg;
		// メッセージが存在するか確認
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// 終了通知が来ている場合は抜ける
			if (msg.message == WM_QUIT) {
				m_isQuitMessage = true;
			}
			else {
				// メッセージをウインドウプロシージャに転送
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return 0;
		}
		return -1;
	}

	int SystemClass::UpdateKeyboardState() {
		BYTE keyStates[256];
		if (GetKeyboardState(keyStates) == 0) {
			// 失敗すると0が返る
			return -1;
		}

		UpdateKey(keyStates, VK_LBUTTON, Mouse::LEFT_CLICK);
		UpdateKey(keyStates, VK_RBUTTON, Mouse::RIGHT_CLICK);
		UpdateKey(keyStates, VK_RETURN, Key::RETURN);
		UpdateKey(keyStates, VK_ESCAPE, Key::ESC);
		UpdateKey(keyStates, VK_SPACE, Key::SPACE);
		UpdateKey(keyStates, VK_LEFT, Key::LEFT);
		UpdateKey(keyStates, VK_UP, Key::UP);
		UpdateKey(keyStates, VK_RIGHT, Key::RIGHT);
		UpdateKey(keyStates, VK_DOWN, Key::DOWN);
		UpdateKey2('A', VK_DOWN, Key::A);
		UpdateKey2('B', VK_DOWN, Key::B);
		UpdateKey2('C', VK_DOWN, Key::C);
		UpdateKey2('D', VK_DOWN, Key::D);
		UpdateKey2('E', VK_DOWN, Key::E);
		UpdateKey2('F', VK_DOWN, Key::F);
		UpdateKey2('G', VK_DOWN, Key::G);
		UpdateKey2('H', VK_DOWN, Key::H);
		UpdateKey2('I', VK_DOWN, Key::I);
		UpdateKey2('J', VK_DOWN, Key::J);
		UpdateKey2('K', VK_DOWN, Key::K);
		UpdateKey2('L', VK_DOWN, Key::L);
		UpdateKey2('M', VK_DOWN, Key::M);
		UpdateKey2('N', VK_DOWN, Key::N);
		UpdateKey2('O', VK_DOWN, Key::O);
		UpdateKey2('P', VK_DOWN, Key::P);
		UpdateKey2('Q', VK_DOWN, Key::Q);
		UpdateKey2('R', VK_DOWN, Key::R);
		UpdateKey2('S', VK_DOWN, Key::S);
		UpdateKey2('T', VK_DOWN, Key::T);
		UpdateKey2('U', VK_DOWN, Key::U);
		UpdateKey2('V', VK_DOWN, Key::V);
		UpdateKey2('W', VK_DOWN, Key::W);
		UpdateKey2('X', VK_DOWN, Key::X);
		UpdateKey2('Y', VK_DOWN, Key::Y);
		UpdateKey2('Z', VK_DOWN, Key::Z);

		return 0;
	}

	int SystemClass::UpdateKey(BYTE* keyStates, int sysKey, int myKey) {
		//0:ボタン離した時
		//1:ボタン押した時(CheckPushKey前)
		//2:ボタン押した時(CheckPushKey後)
		//3:ボタン離した時(CheckPushKey前)
		if (keyStates[sysKey] & 0x80) {
			// 該当キーが押されている場合
			if (m_keyInputs[myKey] == 0) {
				m_keyInputs[myKey] = 1;
			}
		}
		else {
			// 該当キーが押されていない場合
			if (m_keyInputs[myKey] == 1) {
				m_keyInputs[myKey] = 3;
			}
			if (m_keyInputs[myKey] == 2) {
				m_keyInputs[myKey] = 0;
			}
		}
		return 0;
	}

	int SystemClass::UpdateKey2(char chara, int sysKey, int myKey) {
		//0:ボタン離した時
		//1:ボタン押した時(CheckPushKey前)
		//2:ボタン押した時(CheckPushKey後)
		//3:ボタン離した時(CheckPushKey前)
		if (GetAsyncKeyState(chara) & 0x8000) {
			// 該当キーが押されている場合
			if (m_keyInputs[myKey] == 0) {
				m_keyInputs[myKey] = 1;
			}
		}
		else {
			// 該当キーが押されていない場合
			if (m_keyInputs[myKey] == 1) {
				m_keyInputs[myKey] = 3;
			}
			if (m_keyInputs[myKey] == 2) {
				m_keyInputs[myKey] = 0;
			}
		}
		return 0;
	}

	int SystemClass::WindowResizeByClient(HWND hWnd, int width, int height) {
		RECT size;
		RECT wndsize;
		GetClientRect(hWnd, &size);
		GetWindowRect(hWnd, &wndsize);
		wndsize.right = wndsize.right - wndsize.left;
		wndsize.bottom = wndsize.bottom - wndsize.top;
		SetWindowPos(hWnd
			, NULL
			, CW_USEDEFAULT
			, CW_USEDEFAULT
			, width + wndsize.right - size.right
			, height + wndsize.bottom - size.bottom
			, WS_VISIBLE | SWP_NOZORDER);
		return 0;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {

		switch (uMessage) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return SystemClass::MessageHandler(hWnd, uMessage, wParam, lParam);
		}
		return 0;
	}
}
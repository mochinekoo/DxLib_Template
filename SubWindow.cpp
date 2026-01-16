#include <Windows.h>
#include <Uxtheme.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <DxLib.h>

#define EXIT_BUTTON_ID 100

namespace {
    MSG msg;
}

LRESULT CALLBACK SubWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
            case EXIT_BUTTON_ID:
            PostQuitMessage(0); //メッセージループ終了（=アプリを終了）
            DestroyWindow(hWnd);
			break;
        }
        break;
    }
    case WM_DESTROY: {
        PostQuitMessage(0); //メッセージループ終了（=アプリを終了）
        DestroyWindow(hWnd);
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int initSubWindow(HINSTANCE hinstance) {
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = "WindowClass";
    wc.lpfnWndProc = SubWindowProc;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "問題が発生したため、ソフトウェアを終了します。", "エラー", MB_OK | MB_ICONERROR);
        return -1;
    }

    HWND hWnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "デバックウインドウ",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400,
        300,
        NULL,
        NULL,
        hinstance,
        NULL
	);

    HWND button = CreateWindow(
        "BUTTON",
        "終了する",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        0,
        0,
		100,
        100,
        hWnd,
        (HMENU)EXIT_BUTTON_ID,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL
	);

    if (hWnd == NULL) {
        MessageBox(NULL, "問題が発生したため、ソフトウェアを終了します。", "エラー", MB_OK | MB_ICONERROR);
        return -1;
    }
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
	return 0;
}

//ウインドウの更新処理。
DWORD WINAPI createSubWindow(LPVOID lpvoid) {
    HINSTANCE hInstance = (HINSTANCE)lpvoid;
	initSubWindow(hInstance);
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	return 0;
}
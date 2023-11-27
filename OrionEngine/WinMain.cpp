#include <Windows.h>
#include <WinBase.h>
#include <math.h>
#include <string>

LRESULT WINAPI WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(
	_In_		HINSTANCE	hInstance, 
	_In_opt_	HINSTANCE	hPrevInstance, 
	_In_		LPWSTR		lpCmdLine, 
	_In_		int			nCmdShow)
{
	const wchar_t pClassName[] = L"Orion window class";
	const wchar_t pWindowName[] = L"Orion";

	// Register window class and create an instance
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = pClassName;
	
	RegisterClassEx(&wc);
	
	HWND hWnd = CreateWindowEx(
		NULL,
		pClassName,
		pWindowName,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		640, 360,
		NULL,
		NULL,
		hInstance,
		nullptr
	);
	ShowWindow(hWnd, SW_NORMAL);

	// Main Loop
	MSG msg;
	BOOL gResult;

	while ( (gResult = GetMessage(&msg, NULL, NULL, NULL)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)	
		return -1;
	else				
		return msg.wParam;
}

LRESULT WINAPI WndProc(
	HWND	hWnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
	{
		static wchar_t title[256] = {};
		static int length = 0;
		title[length] = wParam;
		length++;
		SetWindowText(hWnd, title);
	}
		break;
	case WM_LBUTTONDOWN:
	{
		OutputDebugString(
			(L"X: " + std::to_wstring(LOWORD(lParam)) + 
			L"\tY: " + std::to_wstring(HIWORD(lParam)) + L"\n")
			.c_str());
	}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
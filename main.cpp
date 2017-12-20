#include "easy.h"
#include <windows.h>
#include <windowsx.h>
#include <memory.h>
#include <malloc.h>
#include <memory>
#include <stdlib.h>
#include <tchar.h>
#include <string>

HINSTANCE g_hInstance = 0;
HWND  g_hWnd;
std::string g_title = "EasyRender";
int g_width = 800, g_height = 600;


//���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//˫�����ͼ
	PAINTSTRUCT ps;
	static HDC s_hdcBackbuffer;			//�󻺳��豸���	
	static HBITMAP s_hBitmap;
	static HBITMAP s_hOldBitmap;

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		break;
	}
	case WM_PAINT:
	{
		break;
	}

	case WM_ERASEBKGND:
		break;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

//����������  
HWND CreateMain(LPCSTR lpClassName, LPCSTR lpWndName)
{
	RECT rc = { 0, 0, g_width, g_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	HWND hWnd = CreateWindowEx(0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, g_hInstance, NULL);
	return hWnd;
}

//ע�ᴰ����  
BOOL Register(LPSTR lpClassName, WNDPROC wndProc)
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wce.hCursor = NULL;
	wce.hIcon = NULL;
	wce.hIconSm = NULL;
	wce.hInstance = g_hInstance;
	wce.lpfnWndProc = wndProc;
	wce.lpszClassName = lpClassName;
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wce);
	if (nAtom == 0)
		return FALSE;
	return TRUE;
}

//��ʾ����  
void Display(HWND hWnd)
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

//��Ϣѭ��  
void Message()
{
	MSG nMsg = { 0 };
	while (nMsg.message != WM_QUIT)
	{
		if (PeekMessage(&nMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		}
		else
		{
			InvalidateRect(g_hWnd, nullptr, true);    //���¿ͻ��˴������»���
			UpdateWindow(g_hWnd);
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance,   //��ǰ����ʵ�����
	_In_opt_ HINSTANCE hPrevInstance,      //��ǰ����ǰһ������ʵ�����
	_In_ LPWSTR lpCmdLine,                 //�����в���
	_In_ int nShowCmd)                     //���ڵ���ʾ��ʽ
{

	g_hInstance = hInstance;
	BOOL nRet = Register("Main", WndProc);
	if (!nRet)
	{
		MessageBox(NULL, "ע��ʧ��", "Infor", MB_OK);
		return 0;
	}
	g_hWnd = CreateMain("Main", g_title.c_str());
	Display(g_hWnd);
	Message();
	return 0;
}



#include "easym.h"
#include "Scene.h"
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

std::shared_ptr<Scene> g_pBoxDemo = std::make_shared<Scene>();

//窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static BITMAPINFO s_bitmapInfo;
	static HDC s_hdcBackbuffer;
	static HBITMAP s_hBitmap;
	static HBITMAP s_hOldBitmap;
	static void* s_pData;

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		g_pBoxDemo->Init(g_hInstance, hWnd);
		//初始化设备无关位图header
		BITMAPINFOHEADER bmphdr = { 0 };
		bmphdr.biSize = sizeof(BITMAPINFOHEADER);
		bmphdr.biWidth = g_width;
		bmphdr.biHeight = -g_height;
		bmphdr.biPlanes = 1;
		bmphdr.biBitCount = 32;
		bmphdr.biSizeImage = g_height * g_width * 4;
		//创建后缓冲区
		//先创建一个内存dc
		s_hdcBackbuffer = CreateCompatibleDC(nullptr);
		//获得前置缓冲区dc
		HDC hdc = GetDC(hWnd);
		if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
			reinterpret_cast<void**>(&g_pBoxDemo->GetDeviceBuffer()), nullptr, 0)))
		{
			MessageBox(nullptr, "create dib section failed!", "error", MB_OK);
			return 0;
		}
		//将bitmap装入内存dc
		s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
		//释放dc
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		//把backbuffer内容传到frontbuffer
		BitBlt(ps.hdc, 0, 0, g_width, g_height, s_hdcBackbuffer, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		SelectObject(s_hdcBackbuffer, s_hOldBitmap);
		DeleteDC(s_hdcBackbuffer);
		DeleteObject(s_hOldBitmap);
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return true;
		break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		g_pBoxDemo->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

		//鼠标释放时
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		g_pBoxDemo->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

		//鼠标移动时
	case WM_MOUSEMOVE:
		g_pBoxDemo->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

//创建主窗口  
HWND CreateMain(LPCSTR lpClassName, LPCSTR lpWndName)
{
	RECT rc = { 0, 0, g_width, g_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
	HWND hWnd = CreateWindowEx(0, lpClassName, lpWndName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, g_hInstance, NULL);
	return hWnd;
}

//注册窗口类  
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

//显示窗口  
void Display(HWND hWnd)
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

//消息循环  
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
			if (g_pBoxDemo->BeInit())
			{
				g_pBoxDemo->Update();
				g_pBoxDemo->Render();
			}
			InvalidateRect(g_hWnd, nullptr, true);    //更新客户端窗口重新绘制
			UpdateWindow(g_hWnd);
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance,   //当前程序实例句柄
	_In_opt_ HINSTANCE hPrevInstance,      //当前程序前一个程序实例句柄
	_In_ LPWSTR lpCmdLine,                 //命令行参数
	_In_ int nShowCmd)                     //窗口的显示方式
{

	g_hInstance = hInstance;
	BOOL nRet = Register("Main", WndProc);
	if (!nRet)
	{
		MessageBox(NULL, "注册失败", "Infor", MB_OK);
		return 0;
	}
	g_hWnd = CreateMain("Main", g_title.c_str());
	
	Display(g_hWnd);
	Message();
	return 0;
}



#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0,
		this->window_class_wide.c_str(),
		this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0,
		0,
		this->width,
		this->height,
		NULL,
		NULL,
		this->hInstance,
		pWindowContainer);
	if (this->handle == NULL) {
		ErrorLogger::Log(GetLastError(), "CreateWindowEx Fail");
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

void RenderWindow::RegisterWindowClass() 
{
	WNDCLASSEX wc; // should be filled before window create
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMessageSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);

}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return 0;
		}

		default:
		{
			WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


/*    callback                */
LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) {
				ErrorLogger::Log("window container error");
				exit(-1);
			}
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);

			//return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		
		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool RenderWindow::ProcessMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//peek all message 
	while(PeekMessage(&msg,
		this->handle,
		0,
		0,
		PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//changed self

	}
	//if no message 
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
		this->handle = NULL;
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		return false;
		}
	}

	return true;
}

HWND RenderWindow::GetHWND() const
{
	return this->handle;
}

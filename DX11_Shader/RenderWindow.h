#pragma once
#include "ErrorLogger.h"

class WindowContainer;


LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
class RenderWindow 
{
public:
	bool Initialize(WindowContainer * pWindowContainer,HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	HWND GetHWND() const;
	
	~RenderWindow();

	

	private:
		void RegisterWindowClass();
		HWND handle = NULL; //Handle to this window
		HINSTANCE hInstance = NULL;
		std::string window_title = "";
		std::wstring window_title_wide = L"";
		std::string window_class = "";
		std::wstring window_class_wide = L"";
		int width = 0;
		int height = 0;
};

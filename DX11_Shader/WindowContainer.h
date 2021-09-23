#pragma once
#include "RenderWindow.h"
#include "KeyboardClass.h"
#include "Mouse/MouseClass.h"
#include "Graphics/Graphics.h"


#include <iostream>
#include <memory>

class WindowContainer {
public:
	WindowContainer();

	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	RenderWindow render_window;
	KeyboardClass keyboard;
	MouseClass mouse;
	Graphics gfx;
private:
};
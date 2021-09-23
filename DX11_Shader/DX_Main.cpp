#include <Windows.h>
#include "Engine.h"
#include "ErrorLogger.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow) {

	//ErrorLogger::Log(S_OK, "Test Message");
	Engine engine;
	engine.Initialize(hInstance, "s", "WinClass", 800, 600);
	
	while (engine.ProcessMessages()) {
		engine.Update();
		engine.RenderFrame();
	}
	//ErrorLogger::Log("exit");

	return 0;
}
#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message) 
{
	std::wstring message_w;
	message_w.append(L"Error: ");
	message_w.append(message.begin(),message.end());
	wchar_t const* error_message =  + message_w.c_str();
	MessageBox(NULL, error_message, L"Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message) 
{
	_com_error error(hr);
	std::wstring error_message = L"Error: " + StringConverter::StringToWide(message) + L"\n" + error.ErrorMessage();
	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}
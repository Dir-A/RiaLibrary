#pragma once
#include <string>


namespace Rut
{
	namespace RxStream
	{
		bool PutConsole(const char* cpStr);
		bool PutConsole(const char* cpStr, size_t nChar);
		bool PutConsole(std::string_view msStr);
		bool PutConsole(const wchar_t* wpStr);
		bool PutConsole(const wchar_t* wpStr, size_t nChar);
		bool PutConsole(std::wstring_view wsStr);
		bool PutConsoleFormat(const char* cpFormat, ...);
		bool PutConsoleFormat(const wchar_t* cpFormat, ...);
		bool PutConsoleMBCS(const char* cpStr, size_t uiCodePage);
		bool PutConsoleMBCS(std::string_view msStr, size_t uiCodePage);
	}
}

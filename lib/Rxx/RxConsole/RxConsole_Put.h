#pragma once


namespace Rut
{
	namespace RxConsole
	{
		bool Put(const char* cpStr);
		bool Put(const char* cpStr, size_t nChar);
		bool Put(const wchar_t* wpStr);
		bool Put(const wchar_t* wpStr, size_t nChar);
		bool Putf(const char* cpFormat, ...);
		bool Putf(const wchar_t* cpFormat, ...);
		bool PutMBCS(const char* cpStr, size_t uiCodePage);
	}
}

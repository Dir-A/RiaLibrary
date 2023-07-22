#include "RxConsole_Put.h"
#include "../RxString.h"

#include <stdio.h>
#include <Windows.h>


namespace Rut
{
	namespace RxConsole
	{
		static constexpr size_t sg_uiBufferCount = 1024;


		bool Put(const char* cpStr)
		{
			return Put(cpStr, strlen(cpStr));
		}

		bool Put(const char* cpStr, size_t nChar)
		{
			return WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), cpStr, nChar, NULL, NULL);
		}

		bool Put(const wchar_t* wpStr)
		{
			return Put(wpStr, wcslen(wpStr));
		}

		bool Put(const wchar_t* wpStr, size_t nChar)
		{
			return WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), wpStr, nChar, NULL, NULL);
		}

		bool PutMBCS(const char* cpStr, size_t uiCodePage)
		{
			std::wstring out_str;
			size_t cch = RxString::ToWCS(cpStr, out_str, uiCodePage);
			return Put(out_str.c_str(), cch);
		}

		bool Putf(const char* cpFormat, ...)
		{
			char buffer[sg_uiBufferCount];

			va_list args = nullptr;
			va_start(args, cpFormat);
			int cch = vsprintf_s(buffer, sg_uiBufferCount, cpFormat, args);
			va_end(args);

			return Put(buffer, cch);
		}

		bool Putf(const wchar_t* cpFormat, ...)
		{
			wchar_t buffer[sg_uiBufferCount];

			va_list args = nullptr;
			va_start(args, cpFormat);
			int cch = vswprintf_s(buffer, sg_uiBufferCount, cpFormat, args);
			va_end(args);

			return Put(buffer, cch);
		}
	}
}
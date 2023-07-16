#include "Str.h"
#include <Windows.h>


namespace Rut
{
	namespace StrX
	{
		std::wstring StrToWStr(const std::string_view msString, size_t uCodePage)
		{
			std::wstring wsString;
			if (StrToWStr(msString, wsString, uCodePage) == 0) { return std::wstring(); }
			return wsString;
		}

		std::string WStrToStr(const std::wstring_view wsString, size_t uCodePage)
		{
			std::string msString;
			if (WStrToStr(wsString, msString, uCodePage) == 0) { return std::string(); }
			return msString;
		}

		size_t StrToWStr(const std::string_view msString, std::wstring& wsString, size_t uCodePage)
		{
			int charCount = MultiByteToWideChar
			(
				uCodePage, NULL, msString.data(), static_cast<int>(msString.size()), NULL, NULL
			);

			if (charCount == 0) { wsString = L""; return 0; }

			wsString.resize(charCount);

			MultiByteToWideChar
			(
				uCodePage, NULL, msString.data(), static_cast<int>(msString.size()), const_cast<wchar_t*>(wsString.data()), charCount
			);

			return charCount;
		}

		size_t WStrToStr(const std::wstring_view wsString, std::string& msString, size_t uCodePage)
		{
			int wcharCount = WideCharToMultiByte
			(
				uCodePage, NULL, wsString.data(), static_cast<int>(wsString.size()), NULL, NULL, NULL, NULL
			);

			if (wcharCount == 0) { msString = ""; return 0; }

			msString.resize(wcharCount);

			WideCharToMultiByte
			(
				uCodePage, NULL, wsString.data(), static_cast<int>(wsString.size()), const_cast<char*>(msString.data()), wcharCount, NULL, NULL
			);

			return wcharCount;
		}
	}
}
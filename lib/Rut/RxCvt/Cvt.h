#pragma once
#include <string>


namespace Rut::RxCvt
{
	std::wstring ToWCS(const std::string_view msStr, size_t uCodePage);
	size_t ToWCS(const std::string_view msStr, std::wstring& wsStr, size_t uCodePage);

	std::string ToMBCS(const std::wstring_view wsStr, size_t uCodePage);
	size_t ToMBCS(const std::wstring_view wsStr, std::string& msStr, size_t uCodePage);

	size_t StrToWStr(const char* cpStr, size_t msStrbytes, wchar_t* wpStr, size_t wsStrLen, size_t nCodePage);
	size_t WStrToStr(const wchar_t* wpStr, size_t wsStrLen, char* cpStr, size_t msStrbytes, size_t nCodePage, bool* isError = nullptr, const char* cpDefault = "?");
}

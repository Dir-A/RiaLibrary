#pragma once
#include <string>

#include "Str_Trim.h"

//Ria's Utility Library X
namespace Rut
{
	namespace StrX
	{
		std::wstring StrToWStr(const std::string_view msString, size_t uCodePage);
		std::string  WStrToStr(const std::wstring_view wsString, size_t uCodePage);
		size_t       StrToWStr(const std::string_view msString, std::wstring& wsString, size_t uCodePage);
		size_t       WStrToStr(const std::wstring_view wsString, std::string& msString, size_t uCodePage);
	}
}
#include "Convert.h"
#include <Windows.h>
#include <stdexcept>


#ifdef WIN32
namespace Rut::RxString
{
	std::wstring ToWCS(const std::string_view msStr, uint32_t uCodePage)
	{
		std::wstring wstr;
		ToWCS(msStr, wstr, uCodePage);
		return wstr;
	}

	std::string ToMBCS(const std::wstring_view wsStr, uint32_t uCodePage)
	{
		std::string mstr;
		ToMBCS(wsStr, mstr, uCodePage);
		return mstr;
	}

	int32_t ToWCS(const std::string_view msStr, std::wstring& wsStr, uint32_t uCodePage)
	{
		int mstr_len = (int)msStr.size();
		if (mstr_len == 0) { wsStr.clear(); return 0; }

		const char* mstr_ptr = msStr.data();
		int wstr_len = MultiByteToWideChar(uCodePage, MB_ERR_INVALID_CHARS, mstr_ptr, mstr_len, nullptr, 0);

		if (wstr_len == 0) { throw std::runtime_error("RxString::ToWCS Error!"); }

		wsStr.resize(wstr_len);
		return MultiByteToWideChar(uCodePage, MB_ERR_INVALID_CHARS, mstr_ptr, mstr_len, wsStr.data(), wstr_len);
	}

	int32_t ToMBCS(const std::wstring_view wsStr, std::string& msStr, uint32_t uCodePage)
	{
		int wstr_len = (int)wsStr.length();
		if (wstr_len == 0) { msStr.clear(); return 0; }

		BOOL not_all_cvt = TRUE;

		const wchar_t* wstr_ptr = wsStr.data();
		int mstr_len = WideCharToMultiByte(uCodePage, 0, wstr_ptr, wstr_len, nullptr, 0, nullptr, &not_all_cvt);

		if (not_all_cvt || (mstr_len == 0)) { throw std::runtime_error("RxString::ToMBCS Error!"); }

		msStr.resize(mstr_len);
		return WideCharToMultiByte(uCodePage, 0, wstr_ptr, wstr_len, msStr.data(), mstr_len, nullptr, nullptr);
	}
}
#endif // WIN32


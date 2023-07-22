#pragma once
#include "RxStream_ANSI.h"


namespace Rut
{
	namespace RxStream
	{
		class OStream_UTF8 final : public OStream_ANSI
		{
		public:
			OStream_UTF8() {};
			OStream_UTF8(const char* cpPath);
			OStream_UTF8(const wchar_t* wpPath);
			OStream_UTF8(std::string_view msPath);
			OStream_UTF8(std::wstring_view wsPath);

			void WriteBOM();

			size_t WriteLine(const wchar_t* cpStr);
			size_t WriteLine(const wchar_t* cpStr, size_t nChar);

		};

		class IStream_UTF8 final : public IStream_ANSI
		{
		public:
			IStream_UTF8() {};
			IStream_UTF8(const char* cpPath);
			IStream_UTF8(const wchar_t* wpPath);
			IStream_UTF8(std::string_view msPath);
			IStream_UTF8(std::wstring_view wsPath);

			void CheckBOM();

			std::wstring GetLine();
			bool GetLine(std::wstring& wsLine);
			size_t ReadLine(wchar_t* pBuffer, size_t nMaxChar);

		};
	}
}
#pragma once
#include "RxStream_Binary.h"


namespace Rut
{
	namespace RxStream
	{
		class OStream_UTF16 final : private OStream_Binary
		{
		public:
			OStream_UTF16() {};
			OStream_UTF16(const char* cpPath);
			OStream_UTF16(const wchar_t* wpPath);
			OStream_UTF16(std::string_view msPath);
			OStream_UTF16(std::wstring_view wsPath);

			void WriteBOM();

			size_t WriteLine(const wchar_t* wpStr);
			size_t WriteLine(const wchar_t* wpStr, size_t nChar);

		};

		class IStream_UTF16 final : private IStream_Binary
		{
		public:
			IStream_UTF16() {};
			IStream_UTF16(const char* cpPath);
			IStream_UTF16(const wchar_t* wpPath);
			IStream_UTF16(std::string_view msPath);
			IStream_UTF16(std::wstring_view wsPath);

			void CheckBOM();

			void MoveNextLine();
			std::wstring GetLine();
			bool GetLine(std::wstring& msLine);
			size_t ReadLine(wchar_t* pBuffer, size_t nMaxChar);

		};
	}
}
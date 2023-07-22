#pragma once
#include "RxStream_Binary.h"


namespace Rut
{
	namespace RxStream
	{
		class OStream_ANSI : public OStream_Binary
		{
		public:
			OStream_ANSI();
			OStream_ANSI(const char* cpPath);
			OStream_ANSI(const wchar_t* wpPath);
			OStream_ANSI(std::string_view msPath);
			OStream_ANSI(std::wstring_view wsPath);

			size_t WriteLine(const char* cpStr);
			size_t WriteLine(const char* cpStr, size_t nChar);
			size_t WriteLine(std::string_view msStr);

		};

		class IStream_ANSI : public IStream_Binary
		{
		public:
			IStream_ANSI();
			IStream_ANSI(const char* cpPath);
			IStream_ANSI(const wchar_t* wpPath);
			IStream_ANSI(std::string_view msPath);
			IStream_ANSI(std::wstring_view wsPath);

			void MoveNextLine();
			std::string GetLine();
			bool GetLine(std::string& msLine);
			size_t ReadLine(char* pBuffer, size_t nMaxChar);

		};
	}
}
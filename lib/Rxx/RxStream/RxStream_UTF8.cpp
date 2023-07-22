#include "RxStream_UTF8.h"
#include "../RxString.h"

using namespace Rut::RxString;


namespace Rut
{
	namespace RxStream
	{
		OStream_UTF8::OStream_UTF8(const char* cpPath)
		{
			this->Create(cpPath);
			WriteBOM();
		}

		OStream_UTF8::OStream_UTF8(const wchar_t* wpPath)
		{
			this->Create(wpPath);
			WriteBOM();
		}

		OStream_UTF8::OStream_UTF8(std::string_view msPath)
		{
			this->Create(msPath.data());
			WriteBOM();
		}

		OStream_UTF8::OStream_UTF8(std::wstring_view wsPath)
		{
			this->Create(wsPath.data());
			WriteBOM();
		}

		void OStream_UTF8::WriteBOM()
		{
			Write((char*)"\xEF\xBB\xBF", 3);
		}

		size_t OStream_UTF8::WriteLine(const wchar_t* cpStr)
		{
			size_t wchar_len = wcslen(cpStr);
			return WriteLine(cpStr, wchar_len);
		}

		size_t OStream_UTF8::WriteLine(const wchar_t* cpStr, size_t nChar)
		{
			int char_len = WideCharToMultiByte(CP_UTF8, NULL, cpStr, nChar, NULL, NULL, NULL, NULL);
			char* buf = new char[char_len];
			WideCharToMultiByte(CP_UTF8, NULL, cpStr, nChar, buf, char_len, NULL, NULL);
			bool is_write = Write(buf, char_len);
			delete[] buf;
			return is_write;
		}


		IStream_UTF8::IStream_UTF8(const char* cpPath)
		{
			this->Open(cpPath);
			CheckBOM();
		}

		IStream_UTF8::IStream_UTF8(const wchar_t* wpPath)
		{
			this->Open(wpPath);
			CheckBOM();
		}

		IStream_UTF8::IStream_UTF8(std::string_view msPath)
		{
			this->Open(msPath.data());
			CheckBOM();
		}

		IStream_UTF8::IStream_UTF8(std::wstring_view wsPath)
		{
			this->Open(wsPath.data());
			CheckBOM();
		}

		void IStream_UTF8::CheckBOM()
		{
			uint32_t bom = ReadUInt32() & 0x00FFFFFFU;
			if (bom != 0x00BFBBEFU)
			{
				MovePointer(-4); // Not BOM Back Pointer
			}
			else
			{
				MovePointer(-1); // Skip BOM
			}
		}

		std::wstring IStream_UTF8::GetLine()
		{
			std::wstring line;
			return GetLine(line) ? line : L"";
		}

		bool IStream_UTF8::GetLine(std::wstring& wsLine)
		{
			std::string u8str;
			if (IStream_ANSI::GetLine(u8str))
			{
				ToWCS(u8str, wsLine, CP_UTF8);
				return true;
			}
			return false;
		}

		size_t IStream_UTF8::ReadLine(wchar_t* pBuffer, size_t nMaxChar)
		{
			std::string u8str;
			std::wstring wsstr;

			u8str.resize(nMaxChar * 2);
			size_t u8char_len = IStream_ANSI::ReadLine(u8str.data(), nMaxChar);

			if (u8char_len == -1)
			{
				return u8char_len;
			}
			else
			{
				ToWCS(u8str, wsstr, CP_UTF8);
				memcpy(pBuffer, wsstr.data(), wsstr.size() * 2);
			}

			return wsstr.length();
		}
	}
}
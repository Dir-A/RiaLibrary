#include "RxStream_UTF16.h"


namespace Rut
{
	namespace RxStream
	{
		void OStream_UTF16::WriteBOM()
		{
			Write((void*)"\xFF\xFE", 2);
		}

		OStream_UTF16::OStream_UTF16(const char* cpPath)
		{
			this->Create(cpPath);
			WriteBOM();
		}

		OStream_UTF16::OStream_UTF16(const wchar_t* wpPath)
		{
			this->Create(wpPath);
			WriteBOM();
		}

		OStream_UTF16::OStream_UTF16(std::string_view msPath)
		{
			this->Create(msPath.data());
			WriteBOM();
		}

		OStream_UTF16::OStream_UTF16(std::wstring_view wsPath)
		{
			this->Create(wsPath.data());
			WriteBOM();
		}

		size_t OStream_UTF16::WriteLine(const wchar_t* wpStr)
		{
			size_t char_count = wcslen(wpStr);
			return WriteLine(wpStr, char_count);
		}

		size_t OStream_UTF16::WriteLine(const wchar_t* wpStr, size_t nChar)
		{
			return Write((wchar_t*)wpStr, nChar * 2);
		}


		void IStream_UTF16::CheckBOM()
		{
			if (ReadUInt16() != 0xFEFF)
			{
				MovePointer(-2); // Not BOM Back Pointer
			}
		}

		IStream_UTF16::IStream_UTF16(const char* cpPath)
		{
			this->Open(cpPath);
			CheckBOM();
		}

		IStream_UTF16::IStream_UTF16(const wchar_t* wpPath)
		{
			this->Open(wpPath);
			CheckBOM();
		}

		IStream_UTF16::IStream_UTF16(std::string_view msPath)
		{
			this->Open(msPath.data());
			CheckBOM();
		}

		IStream_UTF16::IStream_UTF16(std::wstring_view wsPath)
		{
			this->Open(wsPath.data());
			CheckBOM();
		}

		void IStream_UTF16::MoveNextLine()
		{
			ReadLine(0, -1);
		}

		std::wstring IStream_UTF16::GetLine()
		{
			std::wstring line;
			return GetLine(line) ? line : L"";
		}

		bool IStream_UTF16::GetLine(std::wstring& msLine)
		{
			size_t line_len = 0;
			size_t max_char = 0x100;

			while (true)
			{
				msLine.resize(max_char);
				line_len = ReadLine(msLine.data(), max_char);

				if (line_len == -1) // Buffer Too Small
				{
					if (IsEnd()) { return false; }
					max_char <<= 1;
					continue;
				}

				msLine.resize(line_len);
				return true;
			}
		}

		size_t IStream_UTF16::ReadLine(wchar_t* pBuffer, size_t nMaxChar)
		{
			size_t beg_pointer = this->GetPointer();
			if (IsEnd()) { return -1; } // End of File

			wchar_t buffer[0x100];
			wchar_t* buf_ptr = pBuffer;
			size_t line_len = 0;
			while (true)
			{
				size_t ite_char = 0;
				size_t read_size = Read(buffer, sizeof(buffer));
				size_t char_count = read_size / 2;
				for (; ite_char < char_count; ite_char++) { if (buffer[ite_char] == L'\n') { break; } }

				line_len += ite_char;

				if (nMaxChar <= line_len)  // Buffer Too Small
				{
					SetPointer(beg_pointer);
					return -1;
				}

				if (pBuffer != 0 && ite_char != 0) // Do Not Read To Buffer
				{
					memcpy(buf_ptr, buffer, ite_char * sizeof(wchar_t));
					buf_ptr[ite_char] = L'\0';
				}

				if (ite_char != (sizeof(buffer) / 2)) // Read Finish
				{
					size_t skip_size = (line_len + 1) * sizeof(wchar_t);

					if (line_len > 0 && pBuffer != 0) // Delete /r
					{
						if (pBuffer[line_len - 1] == L'\r')
						{
							pBuffer[line_len - 1] = L'\0';
							line_len -= 1;
						}
					}

					SetPointer(beg_pointer + skip_size);
					return line_len;
				}
				else // Read Remain
				{
					buf_ptr += ite_char;
					continue;
				}
			}
		}
	}
}
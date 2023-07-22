#include "RxStream_ANSI.h"


namespace Rut
{
	namespace RxStream
	{
		OStream_ANSI::OStream_ANSI()
		{

		}

		OStream_ANSI::OStream_ANSI(const char* cpPath)
		{
			this->Create(cpPath);
		}

		OStream_ANSI::OStream_ANSI(const wchar_t* wpPath)
		{
			this->Create(wpPath);
		}

		OStream_ANSI::OStream_ANSI(std::string_view msPath)
		{
			this->Create(msPath.data());
		}

		OStream_ANSI::OStream_ANSI(std::wstring_view wsPath)
		{
			this->Create(wsPath.data());
		}

		size_t OStream_ANSI::WriteLine(const char* cpStr)
		{
			size_t char_count = strlen(cpStr);
			return WriteLine((char*)cpStr, char_count);
		}

		size_t OStream_ANSI::WriteLine(const char* cpStr, size_t nChar)
		{
			return Write((char*)cpStr, nChar);
		}

		size_t OStream_ANSI::WriteLine(std::string_view msStr)
		{
			return WriteLine(msStr.data(), msStr.size());
		}


		IStream_ANSI::IStream_ANSI()
		{

		}

		IStream_ANSI::IStream_ANSI(const char* cpPath)
		{
			this->Open(cpPath);
		}

		IStream_ANSI::IStream_ANSI(const wchar_t* wpPath)
		{
			this->Open(wpPath);
		}

		IStream_ANSI::IStream_ANSI(std::string_view msPath)
		{
			this->Open(msPath.data());
		}

		IStream_ANSI::IStream_ANSI(std::wstring_view wsPath)
		{
			this->Open(wsPath.data());
		}

		void IStream_ANSI::MoveNextLine()
		{
			ReadLine(0, -1);
		}

		std::string IStream_ANSI::GetLine()
		{
			std::string line;
			return GetLine(line) ? line : "";
		}

		bool IStream_ANSI::GetLine(std::string& msLine)
		{
			size_t line_len = 0;
			size_t buf_size = 0x100;

			while (true)
			{
				msLine.resize(buf_size);
				line_len = ReadLine(msLine.data(), buf_size);

				if (line_len == -1)
				{
					if (IsEnd()) { return false; }
					buf_size <<= 1;
					continue;
				}

				msLine.resize(line_len);
				return true;
			}
		}

		size_t IStream_ANSI::ReadLine(char* pBuffer, size_t nMaxChar)
		{
			size_t beg_pointer = this->GetPointer();
			if (IsEnd()) { return -1; } // End of File

			char buffer[0x100];
			char* buf_ptr = pBuffer;
			size_t line_len = 0;
			while (true)
			{
				size_t ite_char = 0;
				size_t read_size = Read(buffer, sizeof(buffer));
				for (; ite_char < read_size; ite_char++) { if (buffer[ite_char] == '\n') { break; } }

				line_len += ite_char;

				if (nMaxChar <= line_len)  // Buffer Too Small
				{
					SetPointer(beg_pointer);
					return -1;
				}

				if (pBuffer != 0 && ite_char != 0) // Do Not Read To Buffer
				{
					memcpy(buf_ptr, buffer, ite_char);
					buf_ptr[ite_char] = '\0';
				}

				if (ite_char != sizeof(buffer)) // Read Finish
				{
					size_t skip_size = line_len + 1;

					if (line_len > 0 && pBuffer != 0) // Delete /r
					{
						if (pBuffer[line_len - 1] == '\r')
						{
							pBuffer[line_len - 1] = '\0';
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
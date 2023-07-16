#include "RxStream.h"
#include "Str.h"

using namespace Rut::StrX;


namespace Rut
{
	namespace FileX
	{
		RxOStream_Basic::RxOStream_Basic()
		{
			this->m_hFile = INVALID_HANDLE_VALUE;
		}

		RxOStream_Basic::~RxOStream_Basic()
		{
			Close();
		}

		void RxOStream_Basic::Create(const wchar_t* wpPath)
		{
			m_hFile = CreateFileW(wpPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) { throw std::wstring(L"XStream Create File Error: ") + wpPath; }
		}

		bool RxOStream_Basic::Close()
		{
			bool is_close = CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return is_close;
		}

		size_t RxOStream_Basic::SetPointer(size_t nOffset)
		{
			return SetFilePointer(m_hFile, nOffset, NULL, FILE_BEGIN);
		}

		size_t RxOStream_Basic::MovePointer(size_t nDistance)
		{
			return SetFilePointer(m_hFile, nDistance, NULL, FILE_CURRENT);
		}

		size_t RxOStream_Basic::GetPointer()
		{
			return SetFilePointer(m_hFile, NULL, NULL, FILE_CURRENT);
		}

		size_t RxOStream_Basic::Write(void* pData, size_t nSize)
		{
			DWORD written = 0;
			WriteFile(m_hFile, pData, nSize, &written, NULL);
			return written;
		}

		bool RxOStream_Basic::Flush()
		{
			return FlushFileBuffers(m_hFile);
		}


		RxIStream_Basic::RxIStream_Basic()
		{
			this->m_hFile = INVALID_HANDLE_VALUE;
		}

		RxIStream_Basic::~RxIStream_Basic()
		{
			Close();
		}

		void RxIStream_Basic::Open(const wchar_t* wpPath)
		{
			m_hFile = CreateFileW(wpPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) { throw std::wstring(L"XStream Open File Error: ") + wpPath; }
		}

		bool RxIStream_Basic::Close()
		{
			bool is_close = CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return is_close;
		}

		size_t RxIStream_Basic::MovePointer(size_t nDistance)
		{
			return SetFilePointer(m_hFile, nDistance, NULL, FILE_CURRENT);
		}

		size_t RxIStream_Basic::SetPointer(size_t nOffset)
		{
			return SetFilePointer(m_hFile, nOffset, NULL, FILE_BEGIN);
		}

		size_t RxIStream_Basic::GetPointer()
		{
			return SetFilePointer(m_hFile, NULL, NULL, FILE_CURRENT);
		}

		size_t RxIStream_Basic::GetSize()
		{
			return GetFileSize(m_hFile, NULL);
		}

		size_t RxIStream_Basic::Read(void* pBuffer, size_t nSize)
		{
			DWORD read = 0;
			bool is_read = ReadFile(m_hFile, pBuffer, nSize, &read, NULL);
			return read;
		}

		bool RxIStream_Basic::IsEnd()
		{
			size_t file_size = GetSize();
			size_t current_pointer = GetPointer();
			return current_pointer >= file_size;
		}

		uint8_t RxIStream_Basic::ReadUInt8()
		{
			uint8_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint16_t RxIStream_Basic::ReadUInt16()
		{
			uint16_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint32_t RxIStream_Basic::ReadUInt32()
		{
			uint32_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint64_t RxIStream_Basic::ReadUInt64()
		{
			uint64_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}


		RxOStream_Binary::RxOStream_Binary(const wchar_t* wpPath)
		{
			m_hFile = INVALID_HANDLE_VALUE;
			Create(wpPath);
		}

		RxOStream_Binary::RxOStream_Binary(RxOStream_Binary&& refXStream) noexcept
		{
			this->m_hFile = refXStream.m_hFile;
			refXStream.m_hFile = INVALID_HANDLE_VALUE;
		}

		void RxOStream_Binary::Create(const wchar_t* wpPath)
		{
			RxOStream_Basic::Create(wpPath);
		}

		bool RxOStream_Binary::Close()
		{
			return RxOStream_Basic::Close();
		}

		size_t RxOStream_Binary::SetPointer(size_t nOffset)
		{
			return RxOStream_Basic::SetPointer(nOffset);
		}

		size_t RxOStream_Binary::MovePointer(size_t nDistance)
		{
			return RxOStream_Basic::MovePointer(nDistance);
		}

		size_t RxOStream_Binary::GetPointer()
		{
			return RxOStream_Basic::GetPointer();
		}

		size_t RxOStream_Binary::Write(void* pData, size_t nSize)
		{
			return RxOStream_Basic::Write(pData, nSize);
		}

		bool RxOStream_Binary::Flush()
		{
			return RxOStream_Basic::Flush();
		}


		RxIStream_Binary::RxIStream_Binary(const wchar_t* wpPath)
		{
			m_hFile = INVALID_HANDLE_VALUE;
			Open(wpPath);
		}

		RxIStream_Binary::RxIStream_Binary(RxIStream_Binary&& refXStream) noexcept
		{
			m_hFile = refXStream.m_hFile;
			refXStream.m_hFile = INVALID_HANDLE_VALUE;
		}

		void RxIStream_Binary::Open(const wchar_t* wpPath)
		{
			RxIStream_Basic::Open(wpPath);
		}

		bool RxIStream_Binary::Close()
		{
			return RxIStream_Basic::Close();
		}

		size_t RxIStream_Binary::MovePointer(size_t nDistance)
		{
			return RxIStream_Basic::MovePointer(nDistance);
		}

		size_t RxIStream_Binary::SetPointer(size_t nOffset)
		{
			return RxIStream_Basic::SetPointer(nOffset);
		}

		size_t RxIStream_Binary::GetPointer()
		{
			return RxIStream_Basic::GetPointer();
		}

		size_t RxIStream_Binary::GetSize()
		{
			return RxIStream_Basic::GetSize();
		}

		size_t RxIStream_Binary::Read(void* pBuffer, size_t nSize)
		{
			return RxIStream_Basic::Read(pBuffer, nSize);
		}

		bool RxIStream_Binary::IsEnd()
		{
			return RxIStream_Basic::IsEnd();
		}

		uint8_t RxIStream_Binary::ReadUInt8()
		{
			return RxIStream_Basic::ReadUInt8();
		}

		uint16_t RxIStream_Binary::ReadUInt16()
		{
			return RxIStream_Basic::ReadUInt16();
		}

		uint32_t RxIStream_Binary::ReadUInt32()
		{
			return RxIStream_Basic::ReadUInt32();
		}

		uint64_t RxIStream_Binary::ReadUInt64()
		{
			return RxIStream_Basic::ReadUInt64();
		}


		RxOStream_ANSI::RxOStream_ANSI()
		{

		}

		RxOStream_ANSI::RxOStream_ANSI(const wchar_t* wpPath)
		{
			this->Create(wpPath);
		}

		size_t RxOStream_ANSI::WriteLine(const char* cpStr)
		{
			size_t char_count = strlen(cpStr);
			return WriteLine((char*)cpStr, char_count);
		}

		size_t RxOStream_ANSI::WriteLine(const char* cpStr, size_t nChar)
		{
			return Write((char*)cpStr, nChar);
		}


		RxIStream_ANSI::RxIStream_ANSI()
		{

		}

		RxIStream_ANSI::RxIStream_ANSI(const wchar_t* wpPath)
		{
			this->Open(wpPath);
		}

		void RxIStream_ANSI::MoveNextLine()
		{
			ReadLine(0, -1);
		}

		bool RxIStream_ANSI::GetLine(std::string& msLine)
		{
			size_t line_len = 0;
			size_t buf_size = 0x100;

			while (true)
			{
				msLine.resize(buf_size);
				line_len = ReadLine(msLine.data(), buf_size);

				if (line_len == -1) // Buffer Too Small
				{
					if (IsEnd()) { return false; }
					buf_size <<= 1;
					continue;
				}

				msLine.resize(line_len);
				return true;
			}
		}

		size_t RxIStream_ANSI::ReadLine(char* pBuffer, size_t nMaxChar)
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
				for (; ite_char < read_size; ite_char++){ if (buffer[ite_char] == '\n') { break; } }

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


		void RxOStream_UTF8::WriteBOM()
		{
			Write((char*)"\xEF\xBB\xBF", 3);
		}

		RxOStream_UTF8::RxOStream_UTF8(const wchar_t* wpPath)
		{
			this->Create(wpPath);
			WriteBOM();
		}

		size_t RxOStream_UTF8::WriteLine(const wchar_t* cpStr)
		{
			size_t wchar_len = wcslen(cpStr);
			return WriteLine(cpStr, wchar_len);
		}

		size_t RxOStream_UTF8::WriteLine(const wchar_t* cpStr, size_t nChar)
		{
			int char_len = WideCharToMultiByte(CP_UTF8, NULL, cpStr, nChar, NULL, NULL, NULL, NULL);
			char* buf = new char[char_len];
			WideCharToMultiByte(CP_UTF8, NULL, cpStr, nChar, buf, char_len, NULL, NULL);
			bool is_write = Write(buf, char_len);
			delete[] buf;
			return is_write;
		}


		void RxIStream_UTF8::CheckBOM()
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

		RxIStream_UTF8::RxIStream_UTF8(const wchar_t* wpPath)
		{
			this->Open(wpPath);
			CheckBOM();
		}

		bool RxIStream_UTF8::GetLine(std::wstring& wsLine)
		{
			std::string u8str;
			if (RxIStream_ANSI::GetLine(u8str))
			{
				StrToWStr(u8str, wsLine, CP_UTF8);
				return true;
			}
			return false;
		}

		size_t RxIStream_UTF8::ReadLine(wchar_t* pBuffer, size_t nMaxChar)
		{
			std::string u8str;
			std::wstring wsstr;

			u8str.resize(nMaxChar * 2);
			size_t u8char_len = RxIStream_ANSI::ReadLine(u8str.data(), nMaxChar);

			if (u8char_len == -1)
			{
				return u8char_len;
			}
			else
			{
				StrToWStr(u8str, wsstr, CP_UTF8);
				memcpy(pBuffer, wsstr.data(), wsstr.size() * 2);
			}

			return wsstr.length();
		}


		void RxOStream_UTF16::WriteBOM()
		{
			Write((void*)"\xFF\xFE", 2);
		}

		RxOStream_UTF16::RxOStream_UTF16(const wchar_t* wpPath)
		{
			this->Create(wpPath);
			WriteBOM();
		}

		size_t RxOStream_UTF16::WriteLine(const wchar_t* wpStr)
		{
			size_t char_count = wcslen(wpStr);
			return WriteLine(wpStr, char_count);
		}

		size_t RxOStream_UTF16::WriteLine(const wchar_t* wpStr, size_t nChar)
		{
			return Write((wchar_t*)wpStr, nChar * 2);
		}


		void RxIStream_UTF16::CheckBOM()
		{
			if (ReadUInt16() != 0xFEFF)
			{
				MovePointer(-2); // Not BOM Back Pointer
			}
		}

		RxIStream_UTF16::RxIStream_UTF16()
		{

		}

		RxIStream_UTF16::RxIStream_UTF16(const wchar_t* wpPath)
		{
			this->Open(wpPath);
			CheckBOM();
		}

		void RxIStream_UTF16::MoveNextLine()
		{
			ReadLine(0, -1);
		}

		bool RxIStream_UTF16::GetLine(std::wstring& msLine)
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

		size_t RxIStream_UTF16::ReadLine(wchar_t* pBuffer, size_t nMaxChar)
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

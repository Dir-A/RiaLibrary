#include "RxStream_Binary.h"
#include "../RxPath.h"
#include "../RxString.h"


namespace Rut
{
	namespace RxStream
	{
		OStream_Binary::OStream_Binary() : m_hFile(INVALID_HANDLE_VALUE)
		{

		}

		OStream_Binary::OStream_Binary(const char* cpPath) : m_hFile(INVALID_HANDLE_VALUE)
		{
			Create(cpPath);
		}

		OStream_Binary::OStream_Binary(const wchar_t* wpPath) : m_hFile(INVALID_HANDLE_VALUE)
		{
			Create(wpPath);
		}

		OStream_Binary::OStream_Binary(std::string_view msPath)
		{
			Create(msPath.data());
		}

		OStream_Binary::OStream_Binary(std::wstring_view wsPath) : m_hFile(INVALID_HANDLE_VALUE)
		{
			Create(wsPath.data());
		}

		OStream_Binary::OStream_Binary(OStream_Binary&& refXStream) noexcept : m_hFile(INVALID_HANDLE_VALUE)
		{
			this->m_hFile = refXStream.m_hFile;
			refXStream.m_hFile = INVALID_HANDLE_VALUE;
		}

		OStream_Binary::~OStream_Binary()
		{
			Close();
		}

		void OStream_Binary::Create(const char* cpPath)
		{
			Create(RxString::ToWCS(cpPath, CP_ACP).c_str());
		}

		void OStream_Binary::Create(const wchar_t* wpPath)
		{
			m_hFile = CreateFileW(wpPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) { throw std::runtime_error("RxStream Create File Error!"); }
		}

		void OStream_Binary::Create(std::string_view msPath)
		{
			Create(msPath.data());
		}

		void OStream_Binary::Create(std::wstring_view wsPath)
		{
			Create(wsPath.data());
		}

		bool OStream_Binary::Close()
		{
			bool is_close = CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return is_close;
		}

		size_t OStream_Binary::SetPointer(size_t nOffset)
		{
			return SetFilePointer(m_hFile, nOffset, NULL, FILE_BEGIN);
		}

		size_t OStream_Binary::MovePointer(size_t nDistance)
		{
			return SetFilePointer(m_hFile, nDistance, NULL, FILE_CURRENT);
		}

		size_t OStream_Binary::GetPointer()
		{
			return SetFilePointer(m_hFile, NULL, NULL, FILE_CURRENT);
		}

		size_t OStream_Binary::Write(void* pData, size_t nSize)
		{
			DWORD written = 0;
			WriteFile(m_hFile, pData, nSize, &written, NULL);
			return written;
		}

		bool OStream_Binary::Flush()
		{
			return FlushFileBuffers(m_hFile);
		}


		IStream_Binary::IStream_Binary() : m_hFile(INVALID_HANDLE_VALUE)
		{

		}

		IStream_Binary::IStream_Binary(const char* cpPath) : m_hFile(INVALID_HANDLE_VALUE)
		{
			Open(cpPath);
		}

		IStream_Binary::IStream_Binary(const wchar_t* wpPath) : m_hFile(INVALID_HANDLE_VALUE)
		{
			Open(wpPath);
		}

		IStream_Binary::IStream_Binary(std::string_view msPath)
		{
			Open(msPath.data());
		}

		IStream_Binary::IStream_Binary(std::wstring_view wsPath)
		{
			Open(wsPath.data());
		}

		IStream_Binary::IStream_Binary(IStream_Binary&& refXStream) noexcept : m_hFile(INVALID_HANDLE_VALUE)
		{
			this->m_hFile = refXStream.m_hFile;
			refXStream.m_hFile = INVALID_HANDLE_VALUE;
		}

		IStream_Binary::~IStream_Binary()
		{
			Close();
		}

		void IStream_Binary::Open(const char* cpPath)
		{
			Open(RxString::ToWCS(cpPath, CP_ACP).c_str());
		}

		void IStream_Binary::Open(const wchar_t* wpPath)
		{
			m_hFile = CreateFileW(wpPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hFile == INVALID_HANDLE_VALUE) { throw std::runtime_error("RxStream Open File Error!"); }
		}

		void IStream_Binary::Open(std::string_view msPath)
		{
			Open(msPath.data());
		}

		void IStream_Binary::Open(std::wstring_view wsPath)
		{
			Open(wsPath.data());
		}

		bool IStream_Binary::Close()
		{
			bool is_close = CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
			return is_close;
		}

		size_t IStream_Binary::MovePointer(size_t nDistance)
		{
			return SetFilePointer(m_hFile, nDistance, NULL, FILE_CURRENT);
		}

		size_t IStream_Binary::SetPointer(size_t nOffset)
		{
			return SetFilePointer(m_hFile, nOffset, NULL, FILE_BEGIN);
		}

		size_t IStream_Binary::GetPointer()
		{
			return SetFilePointer(m_hFile, NULL, NULL, FILE_CURRENT);
		}

		size_t IStream_Binary::GetSize()
		{
			return ::GetFileSize(m_hFile, NULL);
		}

		size_t IStream_Binary::Write(void* pData, size_t nSize)
		{
			DWORD written = 0;
			WriteFile(m_hFile, pData, nSize, &written, NULL);
			return written;
		}

		size_t IStream_Binary::Read(void* pBuffer, size_t nSize)
		{
			DWORD read = 0;
			bool is_read = ReadFile(m_hFile, pBuffer, nSize, &read, NULL);
			return read;
		}

		bool IStream_Binary::IsEnd()
		{
			size_t file_size = GetSize();
			size_t current_pointer = GetPointer();
			return current_pointer >= file_size;
		}

		uint8_t IStream_Binary::ReadUInt8()
		{
			uint8_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint16_t IStream_Binary::ReadUInt16()
		{
			uint16_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint32_t IStream_Binary::ReadUInt32()
		{
			uint32_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		uint64_t IStream_Binary::ReadUInt64()
		{
			uint64_t read = 0;
			Read(&read, sizeof(read));
			return read;
		}

		void SaveFileViaPath(const char* cpPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(RxString::ToWCS(cpPath, CP_ACP).c_str(), pData, nBytes);
		}

		void SaveFileViaPath(const wchar_t* wpPath, void* pData, size_t nBytes)
		{
			RxPath::MakeDirViaPath(wpPath);
			RxStream::OStream_Binary rxostream{ wpPath };
			rxostream.Write(pData, nBytes);
		}

		void SaveFileViaPath(std::string_view msPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(msPath.data(), pData, nBytes);
		}

		void SaveFileViaPath(std::wstring_view wsPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(wsPath.data(), pData, nBytes);
		}
	}
}
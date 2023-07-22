#pragma once
#include <string>
#include <stdexcept>
#include <Windows.h>


namespace Rut
{
	namespace RxStream
	{
		class OStream_Binary
		{
		private:
			HANDLE m_hFile;

		public:
			OStream_Binary();
			OStream_Binary(const char* cpPath);
			OStream_Binary(const wchar_t* wpPath);
			OStream_Binary(std::string_view msPath);
			OStream_Binary(std::wstring_view wsPath);
			OStream_Binary(OStream_Binary&& refXStream) noexcept;
			OStream_Binary(const OStream_Binary& refXStream) = delete;
			~OStream_Binary();

			void Create(const char* cpPath);
			void Create(const wchar_t* wpPath);
			void Create(std::string_view msPath);
			void Create(std::wstring_view wsPath);

			bool Close();

			size_t SetPointer(size_t nOffset);
			size_t MovePointer(size_t nDistance);
			size_t GetPointer();

			size_t Write(void* pData, size_t nSize);
			bool   Flush();
		};

		class IStream_Binary
		{
		private:
			HANDLE m_hFile;

		public:
			IStream_Binary();
			IStream_Binary(const char* cpPath);
			IStream_Binary(const wchar_t* wpPath);
			IStream_Binary(std::string_view msPath);
			IStream_Binary(std::wstring_view wsPath);
			IStream_Binary(IStream_Binary&& refXStream) noexcept;
			IStream_Binary(const IStream_Binary& refXStream) = delete;
			~IStream_Binary();

			void Open(const char* cpPath);
			void Open(const wchar_t* wpPath);
			void Open(std::string_view msPath);
			void Open(std::wstring_view wsPath);
			bool Close();

			size_t MovePointer(size_t nDistance);
			size_t SetPointer(size_t nOffset);
			size_t GetPointer();
			size_t GetSize();

			size_t Write(void* pData, size_t nSize);
			size_t Read(void* pBuffer, size_t nSize);
			bool   IsEnd();

			uint8_t ReadUInt8();
			uint16_t ReadUInt16();
			uint32_t ReadUInt32();
			uint64_t ReadUInt64();
		};

		void SaveFileViaPath(const char* cpPath, void* pData, size_t nBytes);
		void SaveFileViaPath(const wchar_t* wpPath, void* pData, size_t nBytes);
		void SaveFileViaPath(std::string_view msPath, void* pData, size_t nBytes);
		void SaveFileViaPath(std::wstring_view wsPath, void* pData, size_t nBytes);

		template <typename T_FileName>
		std::streamsize GetFileSize(const T_FileName& tFile)
		{
			std::ifstream ifs(tFile, std::ios::binary);
			if (!ifs) { throw std::runtime_error("GetFileSize: Open File Error!"); }

			ifs.seekg(0, std::ios::end);
			return ifs.tellg();
		}

		template <typename T_Stream>
		std::streamsize GetFileSize(T_Stream& tStream)
		{
			std::streamsize file_size = 0;
			std::streampos file_pos = tStream.tellg();

			tStream.seekg(0, std::ios::end);
			file_size = tStream.tellg();
			tStream.seekg(file_pos, std::ios::beg);

			return file_size;
		}
	}
}
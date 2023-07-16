#pragma once
#include <Windows.h>
#include <string>


namespace Rut
{
	namespace FileX
	{
		class RxOStream_Basic
		{
		protected:
			HANDLE m_hFile;

		protected:
			RxOStream_Basic();
			~RxOStream_Basic();

		protected:
			void Create(const wchar_t* wpPath);
			bool Close();

			size_t SetPointer(size_t nOffset);
			size_t MovePointer(size_t nDistance);
			size_t GetPointer();

			size_t Write(void* pData, size_t nSize);
			bool   Flush();
		};

		class RxIStream_Basic
		{
		protected:
			HANDLE m_hFile;

		protected:
			RxIStream_Basic();
			RxIStream_Basic(const RxIStream_Basic& refXStream) = delete;
			~RxIStream_Basic();

		protected:
			void Open(const wchar_t* wpPath);
			bool Close();

			size_t MovePointer(size_t nDistance);
			size_t SetPointer(size_t nOffset);
			size_t GetPointer();
			size_t GetSize();

			size_t Read(void* pBuffer, size_t nSize);
			bool   IsEnd();

			uint8_t ReadUInt8();
			uint16_t ReadUInt16();
			uint32_t ReadUInt32();
			uint64_t ReadUInt64();
		};


		class RxOStream_Binary final : private RxOStream_Basic
		{
		public:
			RxOStream_Binary(const wchar_t* wpPath);
			RxOStream_Binary(RxOStream_Binary&& refXStream) noexcept;

			void Create(const wchar_t* wpPath);
			bool Close();

			size_t SetPointer(size_t nOffset);
			size_t MovePointer(size_t nDistance);
			size_t GetPointer();

			size_t Write(void* pData, size_t nSize);
			bool Flush();

		};

		class RxIStream_Binary final : private RxIStream_Basic
		{
		public:
			RxIStream_Binary(const wchar_t* wpPath);
			RxIStream_Binary(RxIStream_Binary&& refXStream) noexcept;

			void Open(const wchar_t* wpPath);
			bool Close();

			size_t MovePointer(size_t nDistance);
			size_t SetPointer(size_t nOffset);
			size_t GetPointer();
			size_t GetSize();

			size_t Read(void* pBuffer, size_t nSize);
			bool IsEnd();

			uint8_t ReadUInt8();
			uint16_t ReadUInt16();
			uint32_t ReadUInt32();
			uint64_t ReadUInt64();
		};


		class RxOStream_ANSI : public RxOStream_Basic
		{
		public:
			RxOStream_ANSI();
			RxOStream_ANSI(const wchar_t* wpPath);

			size_t WriteLine(const char* cpStr);
			size_t WriteLine(const char* cpStr, size_t nChar);

		};

		class RxIStream_ANSI : public RxIStream_Basic
		{
		public:
			RxIStream_ANSI();
			RxIStream_ANSI(const wchar_t* wpPath);

			void MoveNextLine();
			bool GetLine(std::string& msLine);
			size_t ReadLine(char* pBuffer, size_t nMaxChar);

		};


		class RxOStream_UTF8 final : public RxOStream_ANSI
		{
		private:
			void WriteBOM();

		public:
			RxOStream_UTF8(const wchar_t* wpPath);

			size_t WriteLine(const wchar_t* cpStr);
			size_t WriteLine(const wchar_t* cpStr, size_t nChar);

		};

		class RxIStream_UTF8 final : public RxIStream_ANSI
		{
		private:
			void CheckBOM();

		public:
			RxIStream_UTF8(const wchar_t* wpPath);

			bool GetLine(std::wstring& wsLine);
			size_t ReadLine(wchar_t* pBuffer, size_t nMaxChar);

		};


		class RxOStream_UTF16 final : private RxOStream_Basic
		{
		private:
			void WriteBOM();

		public:
			RxOStream_UTF16(const wchar_t* wpPath);

			size_t WriteLine(const wchar_t* wpStr);
			size_t WriteLine(const wchar_t* wpStr, size_t nChar);

		};

		class RxIStream_UTF16 final : private RxIStream_Basic
		{
		private:
			void CheckBOM();

		public:
			RxIStream_UTF16();
			RxIStream_UTF16(const wchar_t* wpPath);

			void MoveNextLine();
			bool GetLine(std::wstring& msLine);
			size_t ReadLine(wchar_t* pBuffer, size_t nMaxChar);

		};

	}
}


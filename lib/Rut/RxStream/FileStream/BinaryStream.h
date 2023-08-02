#pragma once
#include <string>
#include <stdexcept>
#include <Windows.h>

#include "BasicStream.h"


namespace Rut
{
	namespace RxStream
	{
		class BinaryStream : public BasicStream
		{
		public:
			BinaryStream();
			BinaryStream(const char* cpPath, RIO emAccess, RCO emCreate = RCO::RCO_AUTO);
			BinaryStream(const wchar_t* wpPath, RIO emAccess, RCO emCreate = RCO::RCO_AUTO);
			BinaryStream(std::string_view msPath, RIO emAccess, RCO emCreate = RCO::RCO_AUTO);
			BinaryStream(std::wstring_view wsPath, RIO emAccess, RCO emCreate = RCO::RCO_AUTO);
			BinaryStream(const BinaryStream& refStream) = delete;
			~BinaryStream();

			template <typename TYPE> operator TYPE() { TYPE tmp{ 0 }; Read((TYPE*)&tmp, sizeof(TYPE)); return tmp; }
			template <typename TYPE> BinaryStream& operator >>(TYPE& tType) { Read((void*)&tType, sizeof(TYPE)); return *this; }
			template <typename TYPE> BinaryStream& operator <<(TYPE& tType) { Write((void*)&tType, sizeof(tType)); return *this; }

		};

		void SaveFileViaPath(const char* cpPath, void* pData, uint32_t nBytes);
		void SaveFileViaPath(const wchar_t* wpPath, void* pData, uint32_t nBytes);
		void SaveFileViaPath(std::string_view msPath, void* pData, uint32_t nBytes);
		void SaveFileViaPath(std::wstring_view wsPath, void* pData, uint32_t nBytes);

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
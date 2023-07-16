#pragma once
#include <fstream>

#include "Str.h"


namespace Rut
{
	namespace FileX
	{
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
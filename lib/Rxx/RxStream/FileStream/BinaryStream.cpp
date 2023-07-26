#include "BinaryStream.h"
#include "../../RxPath.h"
#include "../../RxString.h"


namespace Rut
{
	namespace RxStream
	{
		BinaryStream::BinaryStream()
		{

		}

		BinaryStream::BinaryStream(const char* cpPath, RIO emAccess, RCO emCreate)
		{
			Create(cpPath, emAccess, emCreate);
		}

		BinaryStream::BinaryStream(const wchar_t* wpPath, RIO emAccess, RCO emCreate)
		{
			Create(wpPath, emAccess, emCreate);
		}

		BinaryStream::BinaryStream(std::string_view msPath, RIO emAccess, RCO emCreate)
		{
			Create(msPath.data(), emAccess, emCreate);
		}

		BinaryStream::BinaryStream(std::wstring_view wsPath, RIO emAccess, RCO emCreate)
		{
			Create(wsPath.data(), emAccess, emCreate);
		}

		BinaryStream::~BinaryStream()
		{
			Close();
		}

		void SaveFileViaPath(const char* cpPath, void* pData, size_t nBytes)
		{
			SaveFileViaPath(RxString::ToWCS(cpPath, CP_ACP).c_str(), pData, nBytes);
		}

		void SaveFileViaPath(const wchar_t* wpPath, void* pData, size_t nBytes)
		{
			RxPath::MakeDirViaPath(wpPath);
			RxStream::BinaryStream rxostream{ wpPath, RIO::RIO_OUT };
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
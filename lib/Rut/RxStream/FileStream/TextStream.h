#pragma once
#include "BinaryStream.h"
#include "../../RxString.h"


namespace Rut
{
	enum RFM
	{
		RFM_ANSI,
		RFM_UTF8,
		RFM_UTF16
	};
}

namespace Rut::RxStream
{
	static constexpr uint32_t READLINE_ERROR = -1;
	static constexpr uint32_t WRITELINE_ERROR = -1;


	class TextStream : private BasicStream
	{
	private:
		RFM m_rxFormat;

	public:
		TextStream();
		TextStream(const char* cpPath, RIO emAccess, RFM emFormat = RFM::RFM_ANSI, RCO emCreate = RCO::RCO_AUTO);
		TextStream(const wchar_t* wpPath, RIO emAccess, RFM emFormat = RFM::RFM_ANSI, RCO emCreate = RCO::RCO_AUTO);
		TextStream(std::string_view msPath, RIO emAccess, RFM emFormat = RFM::RFM_ANSI, RCO emCreate = RCO::RCO_AUTO);
		TextStream(std::wstring_view wsPath, RIO emAccess, RFM emFormat = RFM::RFM_ANSI, RCO emCreate = RCO::RCO_AUTO);

		TextStream& operator >>(std::string& msStr) { ReadLine(msStr); return *this; }
		TextStream& operator >>(std::wstring& wsStr) { ReadLine(wsStr); return *this; }
		TextStream& operator <<(const char* cpStr) { WriteLine(cpStr); return *this; }
		TextStream& operator <<(const wchar_t* wpStr) { WriteLine(wpStr); return *this; }
		TextStream& operator <<(std::string_view msStr) { WriteLine(msStr.data(), (uint32_t)msStr.size()); return *this; }
		TextStream& operator <<(std::wstring_view wsStr) { WriteLine(wsStr.data(), (uint32_t)wsStr.size()); return *this; }

		void WriteBOM();
		void CheckBOM();
		void EnsureBOM(RIO emAccess);

		uint32_t WriteLine(const char* cpStr);
		uint32_t WriteLine(const char* cpStr, uint32_t nChar);
		uint32_t WriteLine(std::string_view msStr);
		uint32_t WriteLine(const wchar_t* cpStr);
		uint32_t WriteLine(const wchar_t* cpStr, uint32_t nChar);
		uint32_t WriteLine(std::wstring_view wsStr);

		void MoveNextLine();

		std::string ReadLineA();
		std::wstring ReadLineW();
		bool ReadLine(std::string& msLine);
		bool ReadLine(std::wstring& wsLine);
		uint32_t ReadLine(char* cpBuffer, uint32_t nMaxChar);
		uint32_t ReadLine(wchar_t* wpBuffer, uint32_t nMaxChar);

	private:
		uint32_t ReadLineMBCS(char* cpBuffer, uint32_t nMaxChar);
		uint32_t ReadLineWide(wchar_t* wpBuffer, uint32_t nMaxChar);

	};
}
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

	namespace RxStream
	{
		static constexpr size_t READLINE_ERROR = -1;
		static constexpr size_t WRITELINE_ERROR = -1;


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
			TextStream& operator <<(std::string_view msStr) { WriteLine(msStr.data(), msStr.size()); return *this; }
			TextStream& operator <<(std::wstring_view wsStr) { WriteLine(wsStr.data(), wsStr.size()); return *this; }

			void WriteBOM();
			void CheckBOM();
			void EnsureBOM(RIO emAccess);

			size_t WriteLine(const char* cpStr);
			size_t WriteLine(const char* cpStr, size_t nChar);
			size_t WriteLine(std::string_view msStr);
			size_t WriteLine(const wchar_t* cpStr);
			size_t WriteLine(const wchar_t* cpStr, size_t nChar);
			size_t WriteLine(std::wstring_view wsStr);

			void MoveNextLine();

			std::string ReadLineA();
			std::wstring ReadLineW();
			bool ReadLine(std::string& msLine);
			bool ReadLine(std::wstring& wsLine);
			size_t ReadLine(char* cpBuffer, size_t nMaxChar);
			size_t ReadLine(wchar_t* wpBuffer, size_t nMaxChar);

		private:
			size_t ReadLineMBCS(char* cpBuffer, size_t nMaxChar);
			size_t ReadLineWide(wchar_t* wpBuffer, size_t nMaxChar);

		};
	}
}
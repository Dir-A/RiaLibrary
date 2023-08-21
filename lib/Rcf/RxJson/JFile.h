#pragma once
#include "JValue.h"
#include "../../Rut/RxStream.h"


namespace Rcf::RxJson
{
	using namespace Rut;

	class JFile
	{
	private:
		std::wstring m_wsJson;
		std::wstring::iterator m_iteChar;

	public:
		JFile()
		{

		}


		void SkipWhite()
		{
			while (true)
			{
				wchar_t ch = m_iteChar[0];
				if (ch == L' ' || ch == L'\t' || ch == L'\n' || ch == L'\r')
				{
					m_iteChar++; continue;
				}
				break;
			}
		}

		wchar_t GetToken()
		{
			SkipWhite();

			switch (m_iteChar[0])
			{
			case L'{':case L'}':
			case L'[':case L']':
			case L'"':case L':':case L',':
			case L'n':case L't':case L'f':
			case L'0':case L'1':case L'2':
			case L'3':case L'4':case L'5':
			case L'6':case L'7':case L'8':
			case L'9':case L'-':return m_iteChar[0];
			}

			throw std::runtime_error("Not Find Token");

		}


		void ParseKey(std::wstring& wsKey)
		{
			std::wstring::iterator beg = m_iteChar;
			std::wstring::iterator end = std::find(beg, m_wsJson.end(), '"');
			wsKey = { beg, end };
			m_iteChar = end + 1;
		}

		bool ParseValue(JValue& rfJValue)
		{
			switch (m_iteChar[0])
			{
			// object
			case L'{': ParseObject(rfJValue); break;
			// array
			case L'[': ParseArray(rfJValue); break;
			// true
			case L't': { m_iteChar += 4; rfJValue = true; } break;
			// false
			case L'f': { m_iteChar += 5; rfJValue = false; }break;
			// null
			case L'n': { m_iteChar += 4; rfJValue = JValue(); }break;
			// string
			case L'"': ParseString(rfJValue); break;
			// Number
			case L'0':case L'1':case L'2':case L'3':
			case L'4':case L'5':case L'6':case L'7':
			case L'8':case L'9':
			case L'-': ParseNumber(rfJValue); break;

			default: throw std::runtime_error("ParseValue Error!");
			}

			return true;
		}


		void ParseNumber(JValue& rfJValue)
		{
			wchar_t* end = nullptr;

			double num_org = wcstod(m_iteChar._Ptr, &end);
			int num_int = (int)(num_org);
			double num_loss = (double)(num_int);
			if (num_org == num_loss)
			{
				rfJValue = (int)num_int;
			}
			else
			{
				rfJValue = num_org;
			}

			m_iteChar._Ptr = end;
		}

		void ParseString(JValue& rfJValue)
		{
			m_iteChar++;

			wchar_t ch = 0;
			std::wstring text;
			while (true)
			{
				ch = m_iteChar[0];

				if (ch == L'\\') // format string
				{
					m_iteChar++;
					wchar_t escape = m_iteChar[0];
					switch (escape)
					{
					case L'\\': escape = L'\\'; break;
					case L'"': escape = L'\"'; break;
					case L'b': escape = L'\b'; break;
					case L'f': escape = L'\f'; break;
					case L'n': escape = L'\n'; break;
					case L'r': escape = L'\r'; break;
					case L't': escape = L'\t'; break;
					case L'u':
					{
						wchar_t* end = nullptr;
						short hex4 = (short)wcstol(m_iteChar._Ptr, &end, 16);
						ch = (wchar_t)hex4;
						m_iteChar += 4;
					}
					break;

					default: throw std::runtime_error("Unknow String Format");
					}
				}

				if (ch == L'"') //end
				{
					m_iteChar++; // skip " char
					break;
				}
				else
				{
					text.append(1, ch);
					m_iteChar++; // netx char
				}

			}

			JValue value{ text };
			rfJValue = std::move(value);
		}

		void ParseArray(JValue& rfJValue)
		{
			m_iteChar++;

			while (true)
			{
				switch (GetToken())
				{
				case L',': // end of element
				{
					m_iteChar++;
				}
				break;

				case L']': // end of array
				{
					m_iteChar++;
					rfJValue.SureArray();
					return;
				}
				break;

				default: // parse value
				{
					JValue value;
					ParseValue(value);
					rfJValue.Append(std::move(value));
				}
				}
			}
		}

		void ParseObject(JValue& rfJValue)
		{
			m_iteChar++;

			std::wstring key;
			while (true)
			{
				switch (GetToken())
				{
				case L'"': // check if key
				{
					m_iteChar++;
					ParseKey(key);
					if (key == L"nowShow")
					{
						int a = 0;
					}
				}
				break;

				case L':': // check key : value
				{
					m_iteChar++;
					SkipWhite();
					JValue value;
					ParseValue(value);
					rfJValue.AddKey(key, std::move(value));
				}
				break;

				case L',': // check end of key / value
				{
					m_iteChar++;
				}
				break;

				case L'}': // end of object
				{
					m_iteChar++;
					rfJValue.SureObject();
					return;
				}
				break;

				default:
				{
					throw std::runtime_error("ParseObject Error!");
				}
				}
			}
		}

		bool Parser(JValue& rfJValue)
		{
			if (GetToken() == L'{')
			{
				ParseObject(rfJValue);
			}
			else
			{
				throw std::runtime_error("Not Find Object");
			}

			if (m_iteChar == m_wsJson.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void ReadJsonFile(std::wstring_view wsJson)
		{
			RxStream::Text ifs_json = { wsJson,RIO::RIO_IN, RFM::RFM_UTF8 };
			ifs_json.ReadRawText(m_wsJson);
			m_iteChar = m_wsJson.begin();
		}

	};
}
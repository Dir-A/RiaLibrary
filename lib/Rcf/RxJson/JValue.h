#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>


namespace Rcf::RxJson
{
	class JValue;

	using JString = std::wstring;
	using JArray = std::vector<JValue>;
	using JObject = std::unordered_map<std::wstring, JValue>;

	typedef enum
	{
		JVALUE_NUL,
		JVALUE_BOL,
		JVALUE_INT,
		JVALUE_DBL,
		JVALUE_STR,
		JVALUE_ARY,
		JVALUE_OBJ
	}JValue_Type;

	typedef union
	{
		bool m_bBool;
		int m_iInt;
		double m_dDouble;
		JString* m_pStr;
		JArray* m_pAry;
		JObject* m_pObj;
	}JValue_Value;


	class JValue
	{
	private:
		JValue_Type m_Type;
		JValue_Value m_Value;

	public:
		JValue()
		{
			m_Type = JVALUE_NUL;
			m_Value = { 0 };
		}

		JValue(bool bValue)
		{
			m_Type = JVALUE_BOL;
			m_Value.m_bBool = bValue;
		}

		JValue(int iValue)
		{
			m_Type = JVALUE_INT;
			m_Value.m_iInt = iValue;
		}

		JValue(double dValue)
		{
			m_Type = JVALUE_DBL;
			m_Value.m_dDouble = dValue;
		}

		JValue(const wchar_t* sValue)
		{
			m_Type = JVALUE_STR;
			m_Value.m_pStr = new JString(sValue);
		}

		JValue(std::wstring_view sValue)
		{
			m_Type = JVALUE_STR;
			m_Value.m_pStr = new JString(sValue);
		}

		JValue(const JArray& aValue)
		{
			m_Type = JVALUE_ARY;
			m_Value.m_pAry = new JArray(aValue);
		}

		JValue(const JObject& oValue)
		{
			m_Type = JVALUE_OBJ;
			m_Value.m_pObj = new JObject(oValue);
		}

		JValue(const JValue& rfJValue)
		{
			Copy(rfJValue);
		}

		JValue(JValue&& rfJValue) noexcept
		{
			Move(rfJValue);
		}

		~JValue()
		{
			switch (m_Type)
			{
			case JValue_Type::JVALUE_STR:
			{
				delete m_Value.m_pStr;
			}
			break;

			case JValue_Type::JVALUE_ARY:
			{
				delete m_Value.m_pAry;
			}
			break;

			case JValue_Type::JVALUE_OBJ:
			{
				delete m_Value.m_pObj;
			}
			break;
			}
		}


		JValue& Copy(const JValue& rfJValue)
		{
			this->m_Type = rfJValue.m_Type;
			this->m_Value = rfJValue.m_Value;

			switch (m_Type)
			{
			case JValue_Type::JVALUE_STR:
				this->m_Value.m_pStr = new JString(*(rfJValue.m_Value.m_pStr));
				break;
			case JValue_Type::JVALUE_ARY:
				this->m_Value.m_pAry = new JArray(*(rfJValue.m_Value.m_pAry));
				break;
			case JValue_Type::JVALUE_OBJ:
				this->m_Value.m_pObj = new JObject(*(rfJValue.m_Value.m_pObj));
				break;
			}

			return *this;
		}

		JValue& Move(JValue& rfJValue)
		{
			this->m_Type = rfJValue.m_Type;
			this->m_Value = rfJValue.m_Value;
			rfJValue.m_Type = JVALUE_NUL;
			rfJValue.m_Value = { 0 };
			return *this;
		}


		JValue& operator = (const JValue& rfJValue)
		{
			return Copy(rfJValue);
		}

		JValue& operator = (JValue&& rfJValue) noexcept
		{
			this->~JValue();
			return Move(rfJValue);
		}


		void ToStr(std::wstring& wsText)
		{
			switch (m_Type)
			{
			case JValue_Type::JVALUE_NUL:
			{
				wsText.append(L"null");
			}
			break;

			case JValue_Type::JVALUE_BOL:
			{
				wsText.append((m_Value.m_bBool) ? L"true" : L"false");
			}
			break;

			case JValue_Type::JVALUE_INT:
			{
				wsText.append(std::to_wstring(m_Value.m_iInt));
			}
			break;

			case JValue_Type::JVALUE_DBL:
			{
				wsText.append(std::to_wstring(m_Value.m_dDouble));
			}
			break;

			case JValue_Type::JVALUE_STR:
			{
				wsText.append(1, L'\"');
				// \t \\ \b \ ?
				wsText.append(*(m_Value.m_pStr));
				wsText.append(1, L'\"');
			}
			break;

			case JValue_Type::JVALUE_ARY:
			{
				wsText.append(1, L'[');

				for (auto& value : *(m_Value.m_pAry))
				{
					value.ToStr(wsText);
					wsText.append(1, L',');
				}

				if (wsText.back() == L',') // if null array
				{
					wsText.pop_back();
				}

				wsText.append(1, L']');
			}
			break;

			case JValue_Type::JVALUE_OBJ:
			{
				wsText.append(1, L'{');

				for (auto& value : *(m_Value.m_pObj))
				{
					wsText.append(1, L'\"');
					wsText.append(value.first);
					wsText.append(1, L'\"');
					wsText.append(1, L':');
					value.second.ToStr(wsText);
					wsText.append(1, L',');
				}

				if (wsText.back() == L',') // if null object
				{
					wsText.pop_back();
				}
				wsText.append(1, L'}');
			}
			break;
			}
		}

		std::wstring Format()
		{
			// To Do
			return L"";
		}

		 //Array
		void SureArray()
		{
			if (m_Type == JVALUE_NUL)
			{
				m_Type = JVALUE_ARY;
				m_Value.m_pAry = new JArray();
			}

			if (m_Type != JVALUE_ARY)
			{
				throw std::runtime_error("Error Json Value Not Array!");
			}
		}

		void Append(const JValue& rfJValue)
		{
			SureArray();
			m_Value.m_pAry->push_back(rfJValue);
		}

		void Append(JValue&& rfJValue)
		{
			SureArray();
			m_Value.m_pAry->emplace_back(std::move(rfJValue));
		}

		JArray& ToAry()
		{
			SureArray();
			return *m_Value.m_pAry;
		}


		// Obj
		void SureObject()
		{
			if (m_Type == JVALUE_NUL)
			{
				m_Type = JVALUE_OBJ;
				m_Value.m_pObj = new JObject();
			}
			
			if (m_Type != JVALUE_OBJ)
			{
				throw std::runtime_error("Error Json Value Not Object!");
			}
		}

		void AddKey(std::wstring_view wsKey)
		{
			SureObject();
			(*this->m_Value.m_pObj)[wsKey.data()];
		}

		void AddKey(std::wstring_view wsKey, const JValue& rfJValue)
		{
			SureObject();
			(*this->m_Value.m_pObj)[wsKey.data()] = rfJValue;
		}

		void AddKey(std::wstring_view wsKey, JValue&& rfJValue)
		{
			SureObject();
			(*this->m_Value.m_pObj)[wsKey.data()] = std::move(rfJValue);
		}

		bool HasKey(std::wstring_view wsKey)
		{
			auto ite = m_Value.m_pObj->find(wsKey.data());
			return ite == m_Value.m_pObj->end() ? false : true;
		}

		JObject& ToOBJ()
		{
			SureObject();
			return *(m_Value.m_pObj);
		}


		JValue_Type GetType()
		{
			return m_Type;
		}

		operator bool()
		{
			if (m_Type == JVALUE_BOL) { return m_Value.m_bBool; }
			throw std::runtime_error("Error Json Type!");
		}

		operator int()
		{
			if (m_Type == JVALUE_INT) { return m_Value.m_iInt; }
			throw std::runtime_error("Error Json Type!");
		}

		operator double()
		{
			if (m_Type == JVALUE_DBL) { return m_Value.m_dDouble; }
			throw std::runtime_error("Error Json Type!");
		}

		operator JString&()
		{
			if (m_Type == JVALUE_STR) { return *(m_Value.m_pStr); }
			throw std::runtime_error("Error Json Type!");
		}

		operator JArray& ()
		{
			return this->ToAry();
			throw std::runtime_error("Error Json Type!");
		}

		operator JObject& ()
		{
			return this->ToOBJ();
			throw std::runtime_error("Error Json Type!");
		}
	};

}
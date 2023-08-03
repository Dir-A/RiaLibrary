#pragma once
#include <string>


namespace Rut::RxStream
{
	static constexpr uint32_t AutoMem_AutoSize = -1;

	class AutoMem
	{
	private:
		uint32_t m_szData;
		uint8_t* m_pData;

	public:
		AutoMem();
		AutoMem(const AutoMem& buffer);
		AutoMem(AutoMem&& buffer) noexcept;
		AutoMem(const std::wstring& wsFile);
		AutoMem(const std::wstring& wsFile, uint32_t szFile);
		~AutoMem();

		template <typename T_Ptr> operator T_Ptr* () { return (T_Ptr*)m_pData; }
		template <typename T_Type> operator T_Type () { return (T_Type)m_szData; }
		template <typename T_Size> AutoMem& operator[] (T_Size tSize) { SetSize(tSize); return *this; }

		uint8_t* SetSize(uint32_t szRes);
		uint32_t GetSize();
		uint8_t* GetPtr();

		void     SaveDataToFile(const std::wstring& wsFile);
		uint8_t* LoadFileViaSize(const std::wstring& wsFile, uint32_t szFile = AutoMem_AutoSize);
	};
}
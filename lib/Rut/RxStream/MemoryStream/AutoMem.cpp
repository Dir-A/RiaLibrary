#include "AutoMem.h"
#include "../FileStream/BinaryStream.h"


namespace Rut::RxStream
{
	AutoMem::AutoMem() : m_pData(nullptr), m_szData(0)
	{

	}

	AutoMem::AutoMem(const AutoMem& buffer)
	{
		if (buffer.m_pData != nullptr)
		{
			this->m_szData = buffer.m_szData;
			this->m_pData = new uint8_t[buffer.m_szData];
			memcpy(m_pData, buffer.m_pData, m_szData);
		}
		else
		{
			this->m_pData = nullptr;
			this->m_szData = 0;
		}
	}

	AutoMem::AutoMem(AutoMem&& buffer) noexcept
	{
		this->m_pData = buffer.m_pData;
		this->m_szData = buffer.m_szData;

		buffer.m_pData = nullptr;
		buffer.m_szData = 0;
	}

	AutoMem::AutoMem(const std::wstring& wsFile) : m_pData(nullptr), m_szData(0)
	{
		LoadFileViaSize(wsFile);
	}

	AutoMem::AutoMem(const std::wstring& wsFile, uint32_t szFile) : m_pData(nullptr), m_szData(0)
	{
		LoadFileViaSize(wsFile, szFile);
	}

	AutoMem::~AutoMem()
	{
		if (m_pData != nullptr) { delete[] m_pData; }
		m_szData = 0;
		m_pData = nullptr;
	}

	uint8_t* AutoMem::SetSize(uint32_t szRes)
	{
		if (m_szData == 0)
		{
			m_pData = new uint8_t[szRes];
			m_szData = szRes;
		}

		if (szRes > m_szData)
		{
			delete[] m_pData;
			m_pData = new uint8_t[szRes];
			m_szData = szRes;
		}

		return m_pData;
	}

	uint32_t AutoMem::GetSize()
	{
		return m_szData;
	}

	uint8_t* AutoMem::GetPtr()
	{
		return m_pData;
	}


	void AutoMem::SaveDataToFile(const std::wstring& wsFile)
	{
		SaveFileViaPath(wsFile.c_str(), m_pData, m_szData);
	}

	uint8_t* AutoMem::LoadFileViaSize(const std::wstring& wsFile, uint32_t szFile)
	{
		BinaryStream ifs = { wsFile.c_str(), RIO::RIO_IN };
		if (szFile == AutoMem_AutoSize) { szFile = ifs.GetSize(); }
		ifs.Read(SetSize(szFile), szFile);
		return m_pData;
	}
}
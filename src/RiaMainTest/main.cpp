#include "../../lib/Rut/RxStream.h"
#include <iostream>
#include <chrono>

class RxRecord
{
private:
	std::chrono::steady_clock::time_point m_tpBeg;
	std::chrono::steady_clock::time_point m_tpEnd;
	std::vector<std::chrono::duration<double, std::milli>> m_vcRecord;

public:
	inline void Beg()
	{
		m_tpBeg = std::chrono::steady_clock::now();
	}

	inline void End()
	{
		m_tpEnd = std::chrono::steady_clock::now();
		m_vcRecord.emplace_back((m_tpEnd - m_tpBeg));
	}

	void Log()
	{
		std::chrono::duration<double, std::milli> cout{};

		for (auto& dur : m_vcRecord)
		{
			cout += dur;
			std::cout << dur << "\n";
		}

		std::cout << "Avg:" << cout / m_vcRecord.size() << "\n";

	}
};

using namespace Rut;

int main()
{
	RxRecord record;

	std::vector<std::wstring> text_list;
	for (size_t i = 0; i < 50; i++)
	{
		record.Beg();
		RxStream::Text ifs_text = { L"test.json", RIO::RIO_IN, RFM::RFM_UTF8 };
		ifs_text.ReadAllLine(text_list);
		//RxStream::Text ofs = { L"test_u.json", RIO::RIO_OUT, RFM::RFM_UTF16 };
		//ofs.WriteAllLine(text_list);
		record.End();
	}

	record.Log();



}
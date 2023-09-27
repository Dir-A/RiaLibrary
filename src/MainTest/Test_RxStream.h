#pragma once
#include "../../lib/Rut/RxStream.h"
#include "../../lib/Rut/RxBench.h"

using namespace Rut;


void TestRxStream()
{
	RxBench::Record record;

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

	std::wstring ee;
	RxPath::PathNotSuffix(ee);

	record.Log();
}
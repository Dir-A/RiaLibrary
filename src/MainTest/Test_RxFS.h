#pragma once
#include "../../lib/Rut/RxFS.h"
#include "../../lib/Rut/RxBench.h"

using namespace Rut;


void TestRxFS()
{
	RxBench::Record record;

	std::vector<std::wstring> text_list;
	for (size_t i = 0; i < 50; i++)
	{
		record.Beg();
		RxFS::Text ifs_text = { L"test.json", RIO::RIO_IN, RFM::RFM_UTF8 };
		ifs_text.ReadAllLine(text_list);
		//RxStream::Text ofs = { L"test_u.json", RIO::RIO_OUT, RFM::RFM_UTF16 };
		//ofs.WriteAllLine(text_list);
		record.End();
	}

	std::wstring ee;
	RxPath::NotSuffix(ee);

	record.Log();
}
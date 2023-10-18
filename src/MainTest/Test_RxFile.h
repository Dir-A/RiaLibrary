#pragma once
#include "../../lib/Rut/RxFile.h"
#include "../../lib/Rut/RxBench.h"

using namespace Rut;


void TestRxFile()
{
	RxFile::Text ofs{ L"1.txt", RIO_WRITE, RFM_UTF8 };
	ofs.WriteBOM();
	ofs << L"我是谁";
}
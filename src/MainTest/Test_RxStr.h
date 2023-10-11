#pragma once
#include "../../lib/Rut/RxCvt.h"

using namespace Rut;


void TestRxStr(int argc, char* argv[])
{
	std::wstring str = L"";

	RxCvt::ToWCS(argv[0], str, 936);

	int a = 0;
}
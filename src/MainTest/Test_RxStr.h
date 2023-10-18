#pragma once
#include "../../lib/Rut/RxStr.h"

using namespace Rut;


void TestRxStr(int argc, char* argv[])
{
	std::wstring str = L"";

	RxStr::ToWCS(argv[0], str, 936);

	int a = 0;
}
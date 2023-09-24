#pragma once
#include "../../lib/Rut/RxString.h"

using namespace Rut;


void TestRxString(int argc, char* argv[])
{
	std::wstring str = L"";

	RxString::ToWCS(argv[0], str, 936);

	int a = 0;
}
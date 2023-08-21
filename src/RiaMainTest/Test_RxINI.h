#pragma once
#include <string.h>
#include <iostream>
#include <Windows.h>

#include "../../lib/Rcf/RxINI.h"
#include "../../lib/Rut/RxStream.h"

using namespace Rcf::RxINI;


void TestRxINI()
{
	try
	{
		// Init
		INI_File ini;

		// Parse INI File
		ini.Parse(L"1.ini");

		// Init And Parse INI File
		INI_File ini(L"File.ini");

		// Add
		ini.Add(L"Section1", L"Name", L"The Art of War");
		ini.Add(L"Section1", L"IsSold", true);
		ini.Add(L"Section1", L"Count", 1000);
		ini.Add(L"Section1", L"Price", 112.31);
		ini.Add(L"Section2", L"Name", L"Romance of the Three Kingdoms");

		// Modify
		ini[L"Section1"][L"IsSold"] = false;
		ini[L"Section1"][L"Count"] = 998;

		// Check Node or Key
		bool check_sec1 = ini.Has(L"Section1");
		bool check_sec2 = ini.Has(L"Section10086");
		bool check_name1 = ini.Has(L"Section10086", L"IsSold");
		bool check_name2 = ini.Has(L"Section10086", L"ip");

		// Get Value
		int count = ini.Get(L"Section1", L"Count");
		double price = ini.Get(L"Section1", L"Price");
		bool is_sold = ini.Get(L"Section1", L"IsSold");
		std::wstring name = ini.Get(L"Section1", L"Name");
		std::wstring& ref = ini.Get(L"Section1", L"Name");

		// Dump INI To WString
		std::wstring dump = ini.Dump();

		// Save INI To File
		ini.Save(L"2.ini");
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what() << '\n';
	}
}
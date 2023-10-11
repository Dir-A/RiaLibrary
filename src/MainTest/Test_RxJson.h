#pragma once
#include <string>

#include "../../lib/Rut/RxFS.h"
#include "../../lib/Rut/RxBench.h"
#include "../../lib/RxJson/RxJson.h"

using namespace Rut;


void Func()
{
	RxJson::Value v0;
	RxJson::Value v1 = true;
	RxJson::Value v2 = 789;
	RxJson::Value v3 = 1.23;
	RxJson::Value v4 = L"str";
	RxJson::Value v5 = RxJson::JArray{ 123,321,1.2,"123" };
	RxJson::Value v6 = RxJson::JObject{ std::pair(L"123",6),std::pair(L"666",6),std::pair(L"777",3.2),std::pair(L"888",L"trs") };

	v1 = RxJson::Value(L"123");
	v1 = v2;
	v1 = 456;

	RxJson::Value jv_obj;
	jv_obj.AddKey(L"port", L"192.168.123.1");
	jv_obj.AddKey(L"title", L"The Json Test");
	RxJson::JObject& obj = jv_obj;
	obj[L"boot"] = true;
	obj[L"count"] = 100;
	obj[L"remain"] = 1.2;

	int e = obj[L"count"];
	double ex = obj[L"remain"];

	RxJson::Value jv_arr;
	jv_arr.Append(true);
	jv_arr.Append(1);
	jv_arr.Append(1.2);
	jv_arr.Append(L"123");
	//jv_arr.Append(jv_obj);
	jv_arr.Append(L"666");
	RxJson::JArray& arr = jv_arr;

	arr[0] = false;
	arr[1] = 666;
	arr[2] = 3.14;
	arr[3] = L"321";

	bool b = arr[0];
	int int_number = arr[1];
	double float_number = arr[2];
	std::wstring text = arr[3];
	text = L"10086";

	jv_obj.AddKey(L"inline", jv_arr);

	//RxStream::PutConsole(jv_obj.ToStr());

	int a = 0;
}


void TestRxJson()
{
	//Func();

	//RxBench::Record record;

	RxJson::Value value;
	//RxJson::JObject& obj = value[L"Titles"];
	//Rut::RxJson::Value info_json;
	//obj[L"JP"] = L"Kunado Kokuki";
	//obj[L"EN"] = L"Kunado Kokuki";
	//RxJson::JArray& arr = value[L"Files"];
	//arr.emplace_back(L"sn1010.ps3");
	//arr.emplace_back(L"sn1020.ps3");
	RxJson::Parser parser;
	parser.Open(L"test.json");

	//record.Beg();
	parser.Read(value);
	//record.End();

	//record.Log();

	//RxJson::JArray& texts = value[L"Texts"][L"sn1010.ps3"];


	//record.Beg();
	RxFS::Text ofs_json = { L"1.json",RIO::RIO_OUT, RFM::RFM_UTF16 };
	std::wstring text;
	value.Dump(text);
	ofs_json << text;
	//record.End();

	//record.Log();
}
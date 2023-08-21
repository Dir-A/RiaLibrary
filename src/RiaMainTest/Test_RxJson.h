#pragma once
#include <string>

#include "../../lib/Rcf/RxJson.h"
#include "../../lib/Rut/RxStream.h"
#include "../../lib/Rut/RxBench.h"

using namespace Rcf;
using namespace Rut;


void Func()
{
	RxJson::JValue v0;
	RxJson::JValue v1 = true;
	RxJson::JValue v2 = 789;
	RxJson::JValue v3 = 1.23;
	RxJson::JValue v4 = L"str";
	RxJson::JValue v5 = RxJson::JArray{ 123,321,1.2,"123" };
	RxJson::JValue v6 = RxJson::JObject{ std::pair(L"123",6),std::pair(L"666",6),std::pair(L"777",3.2),std::pair(L"888",L"trs") };

	v1 = RxJson::JValue(L"123");
	v1 = v2;
	v1 = 456;

	RxJson::JValue jv_obj;
	jv_obj.AddKey(L"port", L"192.168.123.1");
	jv_obj.AddKey(L"title", L"The Json Test");
	RxJson::JObject& obj = jv_obj;
	obj[L"boot"] = true;
	obj[L"count"] = 100;
	obj[L"remain"] = 1.2;

	int e = obj[L"count"];
	double ex = obj[L"remain"];

	RxJson::JValue jv_arr;
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

	RxBench::Record record;

	record.Beg();
	RxJson::JValue value;
	RxJson::JFile file;
	file.ReadJsonFile(L"test.json");
	file.Parser(value);
	record.End();

	record.Log();

	record.Beg();
	RxStream::Text ofs_json = { L"1.json",RIO::RIO_OUT, RFM::RFM_UTF16 };
	std::wstring text;
	value.ToStr(text);
	ofs_json << text;
	record.End();

	record.Log();
}
#include <iostream>

#include "..\TDA\CVTString.h"


int main()
{
	std::string mStr = "Œ“ «À≠ƒÿ£ø";
	std::wstring wStr;

	TDA::CVTString::StrToWStr(mStr, wStr, 936);
}
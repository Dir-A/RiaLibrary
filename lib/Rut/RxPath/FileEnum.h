#pragma once
#include <string>
#include <vector>


namespace Rut::RxPath
{
	bool GetFilesPaths(const std::string& msBasePath, std::vector<std::string>& vecList);
	bool GetFilesPaths(const std::wstring& wsBasePath, std::vector<std::wstring>& vecList);

	bool GetFileNames(const std::string& msBasePath, std::vector<std::string>& vecList);
	bool GetFileNames(const std::wstring& wsBasePath, std::vector<std::wstring>& vecList);

	bool GetFolders(const std::string& msFolder, std::vector<std::string>& vecList);
	bool GetFolders(const std::wstring& wsFolder, std::vector<std::wstring>& vecList);

	bool FindFile(const char* cpPath);
	bool FindFile(const wchar_t* wpPath);
	bool FindFile(std::string_view msPath);
	bool FindFile(std::wstring_view wsPath);
}
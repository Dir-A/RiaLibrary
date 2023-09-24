#pragma once
#include <string>
#include <vector>
#include <filesystem>

#ifndef WIN32
namespace Rut::RxPath::Std
{
	bool AllFilePaths(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList);
	bool AllFilePaths(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList);

	bool CurFileNames(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList, bool isAddBasePath = false);
	bool CurFileNames(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList, bool isAddBasePath = false);

	bool CurFolderNames(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList, bool isAddBasePath = false);
	bool CurFolderNames(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList, bool isAddBasePath = false);
}
#endif // WIN32

#ifdef WIN32
namespace Rut::RxPath::inline Win32
{
	bool AllFilePaths(const std::string& msBasePath, std::vector<std::string>& vecList);
	bool AllFilePaths(const std::wstring& wsBasePath, std::vector<std::wstring>& vecList);

	bool CurFileNames(const std::string& msBasePath, std::vector<std::string>& vecList, bool isAddBasePath = false);
	bool CurFileNames(const std::wstring& wsBasePath, std::vector<std::wstring>& vecList, bool isAddBasePath = false);

	bool CurFolderNames(const std::string& msFolder, std::vector<std::string>& vecList, bool isAddBasePath = false);
	bool CurFolderNames(const std::wstring& wsFolder, std::vector<std::wstring>& vecList, bool isAddBasePath = false);
}
#endif // WIN32

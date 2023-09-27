#pragma once
#include <string>
#include <filesystem>


namespace Rut::RxPath
{
	size_t FileName(char* cpPath, size_t nChar);
	size_t FileName(wchar_t* wpPath, size_t nChar);
	void FileNameRef(std::string& msPath);
	void FileNameRef(std::wstring& wsPath);
	std::string FileName(std::string msPath);
	std::wstring FileName(std::wstring wsPath);

	size_t NotFileName(char* cpPath, size_t nChar);
	size_t NotFileName(wchar_t* wpPath, size_t nChar);
	void NotFileNameRef(std::wstring& sPath);
	void NotFileNameRef(std::string& msPath);
	std::string NotFileName(std::string msPath);
	std::wstring NotFileName(std::wstring wsPath);

	size_t Suffix(char* cpPath, size_t nChar);
	size_t Suffix(wchar_t* wpPath, size_t nChar);
	void SuffixRef(std::string& msPath);
	void SuffixRef(std::wstring& wsPath);
	std::string Suffix(std::string msPath);
	std::wstring Suffix(std::wstring wsPath);

	size_t NotSuffix(char* cpPath, size_t nChar);
	size_t NotSuffix(wchar_t* wpPath, size_t nChar);
	void NotSuffixRef(std::string& msPath);
	void NotSuffixRef(std::wstring& wsPath);
	std::string NotSuffix(std::string msPath);
	std::wstring NotSuffix(std::wstring wsPath);

	char* FormatSlash(char* cpPath, char cSlash);
	wchar_t* FormatSlash(wchar_t* wpPath, wchar_t wcSlash);
	void FormatSlashRef(std::string& msPath, char cSlash);
	void FormatSlashRef(std::wstring& wsPath, wchar_t cSlash);
	std::string FormatSlash(std::string msPath, char cSlash);
	std::wstring FormatSlash(std::wstring wsPath, wchar_t wcSlash);
}

#ifndef WIN32
namespace Rut::RxPath::inline Std
{
	template <typename T_STR> bool Exist(const T_STR& tPath)
	{
		return std::filesystem::exists(tPath);
	}

	template <typename T_STR> bool FileExist(const T_STR& tPath)
	{
		return std::filesystem::is_regular_file(tPath);
	}

	template <typename T_STR> bool DirExist(const T_STR& tPath)
	{
		return std::filesystem::is_directory(tPath);
	}

	template <typename T_STR> void MakeDir(const T_STR& tPath)
	{
		std::filesystem::create_directory(tPath);
	}

	template <typename T_STR> void MakeDirViaPath(const T_STR& tPath)
	{
		std::filesystem::create_directories(tPath);
	}

	template <typename T_STR> std::uintmax_t FileSize(const T_STR& tPath)
	{
		return std::filesystem::file_size(tPath);
	}

	std::filesystem::path CurrentPath();


	//template <typename T_STR> std::filesystem::path FileName(const T_STR& tPath)
	//{
	//	return std::filesystem::path(tPath).filename();
	//}

	//template <typename T_STR> std::filesystem::path NotFileName(const T_STR& tPath)
	//{
	//	return std::filesystem::path(tPath).remove_filename();
	//}

	//template <typename T_STR> std::filesystem::path Suffix(const T_STR& tPath)
	//{
	//	return std::filesystem::path(tPath).extension();
	//}

	//template <typename T_STR> std::filesystem::path NotSuffix(const T_STR& tPath)
	//{
	//	return std::filesystem::path(tPath).replace_extension();
	//}

}
#endif // !WIN32

#ifdef WIN32
namespace Rut::RxPath::inline Win32
{
	bool Exist(const char* cpPath);
	bool Exist(const wchar_t* wpPath);
	bool Exist(std::string_view msPath);
	bool Exist(std::wstring_view wsPath);

	bool DirExist(const char* cpPath);
	bool DirExist(const wchar_t* wpPath);
	bool DirExist(std::string_view msPath);
	bool DirExist(std::wstring_view wsPath);

	bool FileExist(const char* cpPath);
	bool FileExist(const wchar_t* wpPath);
	bool FileExist(std::string_view msPath);
	bool FileExist(std::wstring_view wsPath);

	bool MakeDir(const char* cpPath);
	bool MakeDir(const wchar_t* wpPath);
	bool MakeDir(std::string_view msPath);
	bool MakeDir(std::wstring_view wsPath);

	void MakeDirViaPath(const char* cpPath);
	void MakeDirViaPath(const wchar_t* cpPath);
	void MakeDirViaPath(std::string_view msPath);
	void MakeDirViaPath(std::wstring_view wsPath);

	std::uintmax_t FileSize(const char* cpPath);
	std::uintmax_t FileSize(const wchar_t* wpPath);
	std::uintmax_t FileSize(std::string_view msPath);
	std::uintmax_t FileSize(std::wstring_view wsPath);

	size_t ModulePath(char* cpBuf, void* pBase = nullptr);
	size_t ModulePath(wchar_t* wpBuf, void* pBase = nullptr);
	std::string  ModulePathA(void* pBase = nullptr);
	std::wstring ModulePathW(void* pBase = nullptr);

	size_t ModuleName(char* cpBuf, void* pBase = nullptr);
	size_t ModuleName(wchar_t* wpBuf, void* pBase = nullptr);
	std::string ModuleNameA(void* pBase = nullptr);
	std::wstring ModuleNameW(void* pBase = nullptr);

	size_t CurrentDir(char* pPath);
	size_t CurrentDir(wchar_t* pPath);
	std::string  CurrentDirA();
	std::wstring CurrentDirW();

}
#endif // WIN32
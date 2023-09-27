#include "Enum.h"

#include <queue>
#include <Windows.h>

#ifndef WIN32
namespace Rut::RxPath::Std
{
	bool AllFilePaths(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList)
	{
		std::queue<std::filesystem::path> folders;
		folders.push(fsBasePath);

		for (; !folders.empty(); folders.pop())
		{
			for (auto& entry : std::filesystem::directory_iterator(folders.front()))
			{
				if (entry.is_regular_file())
				{
					vecList.push_back(std::move(entry.path().string()));
					continue;
				}

				if (entry.is_directory())
				{
					folders.push(entry.path());
					continue;
				}
			}
		}

		return true;
	}

	bool AllFilePaths(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList)
	{
		std::queue<std::filesystem::path> folders;
		folders.push(fsBasePath);

		for (; !folders.empty(); folders.pop())
		{
			for (auto& entry : std::filesystem::directory_iterator(folders.front()))
			{
				if (entry.is_regular_file())
				{
					vecList.push_back(std::move(entry.path().wstring()));
					continue;
				}

				if (entry.is_directory())
				{
					folders.push(entry.path());
				}
			}
		}

		return true;
	}

	bool CurFileNames(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList, bool isAddBasePath)
	{
		for (auto& entry : std::filesystem::directory_iterator(fsBasePath))
		{
			if (entry.is_regular_file() == false) { continue; }

			if (isAddBasePath)
			{
				vecList.emplace_back(std::move(entry.path().string()));
			}
			else
			{
				vecList.emplace_back(std::move(entry.path().filename().string()));
			}
		}

		return true;
	}

	bool CurFileNames(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList, bool isAddBasePath)
	{
		for (auto& entry : std::filesystem::directory_iterator(fsBasePath))
		{
			if (entry.is_regular_file() == false) { continue; }

			if (isAddBasePath)
			{
				vecList.emplace_back(std::move(entry.path().wstring()));
			}
			else
			{
				vecList.emplace_back(std::move(entry.path().filename().wstring()));
			}
		}

		return true;
	}

	bool CurFolderNames(const std::filesystem::path& fsBasePath, std::vector<std::string>& vecList, bool isAddBasePath)
	{
		for (auto& entry : std::filesystem::directory_iterator(fsBasePath))
		{
			if (entry.is_directory() == false) { continue; }

			if (isAddBasePath)
			{
				vecList.emplace_back(std::move(entry.path().string()));
			}
			else
			{
				vecList.emplace_back(std::move(entry.path().filename().string()));
			}
		}

		return true;
	}

	bool CurFolderNames(const std::filesystem::path& fsBasePath, std::vector<std::wstring>& vecList, bool isAddBasePath)
	{
		for (auto& entry : std::filesystem::directory_iterator(fsBasePath))
		{
			if (entry.is_directory()) { continue; }

			if (isAddBasePath)
			{
				vecList.emplace_back(std::move(entry.path().wstring()));
			}
			else
			{
				vecList.emplace_back(std::move(entry.path().filename().wstring()));
			}
		}

		return true;
	}
}
#endif // !WIN32

#ifdef WIN32
namespace Rut::RxPath::Win32
{
	void CheckPath(std::string_view msPath)
	{
		switch (msPath.back())
		{
		case '\\': break;
		default: throw std::runtime_error("Error Path");
		}
	}

	void CheckPath(std::wstring_view wsPath)
	{
		switch (wsPath.back())
		{
		case L'\\': break;
		default: throw std::runtime_error("Error Path");
		}
	}

	bool AllFilePaths(const std::string& msPath, std::vector<std::string>& vecList)
	{
		CheckPath(msPath);

		std::queue<std::string> dirs;
		WIN32_FIND_DATAA find_data = { 0 };

		dirs.push(msPath);

		for (HANDLE hFind = INVALID_HANDLE_VALUE; !dirs.empty(); dirs.pop())
		{
			std::string& dirName = dirs.front();

			hFind = FindFirstFileA((dirName + "*").c_str(), &find_data);
			if (hFind == INVALID_HANDLE_VALUE) { return false; }

			do
			{
				if (!strcmp(find_data.cFileName, ".") || !strcmp(find_data.cFileName, "..")) { continue; }

				if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					dirs.push(dirName + find_data.cFileName + "\\");
					continue;
				}

				vecList.emplace_back(dirName + find_data.cFileName);

			} while (FindNextFileA(hFind, &find_data));

			FindClose(hFind);
		}

		return true;
	}

	bool AllFilePaths(const std::wstring& wsPath, std::vector<std::wstring>& vecList)
	{
		CheckPath(wsPath);

		std::queue<std::wstring> dirs;
		WIN32_FIND_DATAW find_data = { 0 };

		dirs.push(wsPath);

		for (HANDLE hfile = INVALID_HANDLE_VALUE; !dirs.empty(); dirs.pop())
		{
			std::wstring& dirName = dirs.front();

			hfile = FindFirstFileW((dirName + L"*").c_str(), &find_data);
			if (hfile == INVALID_HANDLE_VALUE) { return false; }

			do
			{
				if (!wcscmp(find_data.cFileName, L".") || !wcscmp(find_data.cFileName, L"..")) { continue; }

				if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					dirs.push(dirName + find_data.cFileName + L"\\");
					continue;
				}

				vecList.emplace_back(dirName + find_data.cFileName);

			} while (FindNextFileW(hfile, &find_data));

			FindClose(hfile);
		}

		return true;
	}

	bool CurFileNames(const std::string& msFolder, std::vector<std::string>& vecList, bool isAddBasePath)
	{
		CheckPath(msFolder);

		WIN32_FIND_DATAA find_data = { 0 };

		HANDLE hfile = FindFirstFileA((msFolder + "*").c_str(), &find_data);
		if (hfile == INVALID_HANDLE_VALUE) { return false; }

		do
		{
			if (!strcmp(find_data.cFileName, ".") || !strcmp(find_data.cFileName, "..")) { continue; }
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

			if (isAddBasePath)
			{
				vecList.emplace_back(msFolder + find_data.cFileName);
			}
			else
			{
				vecList.emplace_back(find_data.cFileName);
			}

		} while (FindNextFileA(hfile, &find_data));

		FindClose(hfile);
		return true;
	}

	bool CurFileNames(const std::wstring& wsFolder, std::vector<std::wstring>& vecList, bool isAddBasePath)
	{
		CheckPath(wsFolder);

		WIN32_FIND_DATAW find_data = { 0 };

		HANDLE hfile = FindFirstFileW((wsFolder + L"*").c_str(), &find_data);
		if (hfile == INVALID_HANDLE_VALUE) { return false; }

		do
		{
			if (!wcscmp(find_data.cFileName, L".") || !wcscmp(find_data.cFileName, L"..")) { continue; }
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;

			if (isAddBasePath)
			{
				vecList.emplace_back(wsFolder + find_data.cFileName);
			}
			else
			{
				vecList.emplace_back(find_data.cFileName);
			}

		} while (FindNextFileW(hfile, &find_data));

		FindClose(hfile);
		return true;
	}

	bool CurFolderNames(const std::string& msFolder, std::vector<std::string>& vecList, bool isAddBasePath)
	{
		CheckPath(msFolder);

		WIN32_FIND_DATAA find_data = { 0 };

		HANDLE hfile = FindFirstFileA((msFolder + "*").c_str(), &find_data);
		if (hfile == INVALID_HANDLE_VALUE) { return false; }

		do
		{
			if (!strcmp(find_data.cFileName, ".") || !strcmp(find_data.cFileName, "..")) { continue; }
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (isAddBasePath)
				{
					vecList.emplace_back(msFolder + find_data.cFileName);
				}
				else
				{
					vecList.emplace_back(find_data.cFileName);
				}
			}

		} while (FindNextFileA(hfile, &find_data));

		FindClose(hfile);
		return true;
	}

	bool CurFolderNames(const std::wstring& wsFolder, std::vector<std::wstring>& vecList, bool isAddBasePath)
	{
		CheckPath(wsFolder);

		WIN32_FIND_DATAW find_data = { 0 };

		HANDLE hfile = FindFirstFileW((wsFolder + L"*").c_str(), &find_data);
		if (hfile == INVALID_HANDLE_VALUE) { return false; }

		do
		{
			if (!wcscmp(find_data.cFileName, L".") || !wcscmp(find_data.cFileName, L"..")) { continue; }
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (isAddBasePath)
				{
					vecList.emplace_back(wsFolder + find_data.cFileName);
				}
				else
				{
					vecList.emplace_back(find_data.cFileName);
				}
			}

		} while (FindNextFileW(hfile, &find_data));

		FindClose(hfile);
		return true;
	}
}
#endif // Win32
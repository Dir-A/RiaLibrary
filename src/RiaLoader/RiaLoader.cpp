#include <stdexcept>
#include <Windows.h>

#include "../../lib/Rut/RxPath.h"
#include "../../lib/Rut/RxINI.h"
#include "../../lib/RxHook/RxHook.h"

using namespace Rut;


INT APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	std::wstring exe_name_noext = RxPath::NotSuffix(RxPath::ModuleNameW(hInstance));

	try
	{
		RxINI::Parser ini{ exe_name_noext + L".ini" };
		std::wstring exe_name = ini[L"RiaLoader"][L"TargetEXE"];
		std::uint32_t dll_count = ini[L"RiaLoader"][L"TargetDLLCount"];

		std::vector<std::string> dll_list;
		for (uint32_t ite_dll = 0; ite_dll < dll_count; ite_dll++)
		{
			dll_list.emplace_back(ini[L"RiaLoader"][std::wstring(L"TargetDLLName_") + std::to_wstring(ite_dll)]);
		}

		const char** dll_name_array = new const char*[dll_count];
		for (size_t ite_dll = 0; ite_dll < dll_count; ite_dll++)
		{
			dll_name_array[ite_dll] = dll_list[ite_dll].c_str();
		}

		if (RxHook::CreateProcessWithDlls(exe_name.c_str(), CREATE_SUSPENDED, dll_count, dll_name_array, &si, &pi))
		{
			if (pi.hThread)
			{
				ResumeThread(pi.hThread);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}
		}
		else
		{
			MessageBoxW(NULL, L"DetourCreateProcessWithDll Failed!", NULL, MB_OK);
		}

		delete[] dll_name_array;
	}
	catch (const std::runtime_error& err)
	{
		MessageBoxA(NULL, err.what(), "RiaLoader", NULL);
		exit(-1);
	}
}
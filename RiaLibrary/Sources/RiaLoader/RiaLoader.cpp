#include <Windows.h>

#include "../../Modules/Rxx/include/File.h"
#include "../../Modules/Rxx/include/Str.h"
#include "../../Modules/Rxx/include/INI.h"
#include "../../ThirdParty/detours/include/detours.h"

#pragma comment(lib,"../../ThirdParty/detours/lib.X86/detours.lib")

using namespace Rcf::INI;
using namespace Rut::FileX;
using namespace Rut::StrX;


INT APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	std::wstring exe_name_noext = PathRemoveExtension(GetFileNameViaBaseW((uint32_t)hInstance));

	try
	{
		INI_File ini(exe_name_noext + L".ini");
		KeysMap& node_ria = ini.Get(L"RiaLoader");
		std::wstring inject_exe_name = node_ria[L"TargetEXE"];
		std::wstring inject_dll_name = node_ria[L"TargetDLL"];
		std::string  inject_dll_name_ms = WStrToStr(inject_dll_name, CP_ACP);

		if (DetourCreateProcessWithDllW(inject_exe_name.c_str(), NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi, inject_dll_name_ms.c_str(), NULL))
		{
			ResumeThread(pi.hThread);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}
		else
		{
			MessageBoxW(NULL, L"DetourCreateProcessWithDll Failed!", NULL, MB_OK);
		}
	}
	catch (const std::runtime_error& err)
	{
		MessageBoxA(NULL, err.what(), "RiaLoader", NULL);
		exit(-1);
	}
}
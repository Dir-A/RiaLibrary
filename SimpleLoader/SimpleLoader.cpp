#include <Windows.h>
#include "../ThirdParty/detours/include/detours.h"

#pragma comment(lib,"../ThirdParty/detours/lib.X86/detours.lib")


INT APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	LPCWSTR applicationName = L"eden_pm_en.exe";
	LPCSTR dllName = "EdenPMHook.dll";

	if (DetourCreateProcessWithDllW(applicationName, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi, dllName, NULL))
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
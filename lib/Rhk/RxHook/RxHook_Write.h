#pragma once
#include <string>
#include <cstdint>
#include <Windows.h>


namespace Rut::RxHook
{
	bool WriteHookCode(uint32_t uiRawAddress, uint32_t uiNewAddress, uint32_t szHookCode);
	bool WriteHookCode_RET(uint32_t uiRawAddress, uint32_t uiRetAddress, uint32_t uiNewAddress);
	bool SetHook(uint32_t uiRawAddr, uint32_t uiTarAddr, uint32_t szRawSize);
	bool DetourAttachFunc(void* ppRawFunc, void* pNewFunc);
	bool DetourDetachFunc(void* ppRawFunc, void* pNewFunc);

	bool CreateProcessWithDlls(std::wstring_view wsAppName, uint32_t uiFlags, uint32_t nDlls, const char** rlpDlls, LPSTARTUPINFOW pStartupInfo, LPPROCESS_INFORMATION pProcessInformation);
}
#pragma once
#include <Windows.h>


namespace Rut::RxHook
{
	BOOL WriteMemory(LPVOID lpAddress, LPCVOID lpBuffer, SIZE_T nSize);
	BOOL ReadMemory(LPVOID lpAddress, LPVOID lpBuffer, SIZE_T nSize);
	DWORD MemSearch(DWORD pFind, SIZE_T szFind, PBYTE pToFind, SIZE_T szToFind, BOOL backward = FALSE);
}



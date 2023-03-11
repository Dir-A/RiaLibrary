#include "MemX.h"


namespace TDA
{
	BOOL MemX::WriteMemory(LPVOID lpAddress, LPCVOID lpBuffer, SIZE_T nSize)
	{
		DWORD oldProtect = 0;
		BOOL isProtect = VirtualProtectEx(GetCurrentProcess(), lpAddress, nSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		BOOL isWritten = WriteProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, nSize, NULL);

		if (isProtect && isWritten) return true;

		MessageBoxW(NULL, L"WriteMemory Failed!!", NULL, NULL);

		return false;
	}

	BOOL MemX::ReadMemory(LPVOID lpAddress, LPVOID lpBuffer, SIZE_T nSize)
	{
		DWORD oldProtect = 0;
		BOOL isProtect = VirtualProtectEx(GetCurrentProcess(), lpAddress, nSize, PAGE_EXECUTE_READWRITE, &oldProtect);
		BOOL isWritten = ReadProcessMemory(GetCurrentProcess(), lpAddress, lpBuffer, nSize, NULL);

		if (isProtect && isWritten) return true;

		MessageBoxW(NULL, L"ReadMemory Failed!!", NULL, NULL);

		return false;
	}

	BOOL MemX::WriteHookCode(DWORD dwRawAddress, DWORD dwNewAddress, SIZE_T szHookCode)
	{
		BYTE code[0xF];
		memset(code, 0x90, 0xF);

		*(BYTE*)(code + 0) = 0xE9;
		*(DWORD*)(code + 1) = dwNewAddress - dwRawAddress - 5;

		if (WriteMemory((LPVOID)dwRawAddress, &code, szHookCode)) return true;

		MessageBoxW(NULL, L"WriteHookCode Failed!!", NULL, NULL);

		return false;
	}

	BOOL MemX::SetHook(DWORD dwRawAddr, DWORD dwTarAddr, SIZE_T szRawSize)
	{
		BOOL isProtect = 0;
		DWORD oldProtect = 0;
		PBYTE allocateAddr = 0;
		DWORD relativeAddr = 0;
		BYTE rawJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
		BYTE retJmp[] = { 0xE9,0x00,0x00,0x00,0x00 };
		BYTE tarCal[] = { 0xE8,0x00,0x00,0x00,0x00 };

		isProtect = VirtualProtect((LPVOID)dwRawAddr, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtect);
		allocateAddr = (PBYTE)VirtualAlloc(NULL, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (allocateAddr && isProtect)
		{
			//Copy the Code for the original address to alloc address
			memcpy(allocateAddr, (PVOID)dwRawAddr, szRawSize);

			//Write Jmp Code
			relativeAddr = (DWORD)allocateAddr - dwRawAddr - sizeof(rawJmp);
			memcpy(&rawJmp[1], &relativeAddr, sizeof(DWORD));
			memcpy((PBYTE)dwRawAddr, rawJmp, sizeof(rawJmp));

			//Write Call TarFunc Code
			relativeAddr = dwTarAddr - (DWORD)(&allocateAddr[szRawSize]) - sizeof(tarCal);
			memcpy(&tarCal[1], &relativeAddr, sizeof(DWORD));
			memcpy(&allocateAddr[szRawSize], tarCal, sizeof(tarCal));

			//Write Ret Code
			relativeAddr = (dwRawAddr + szRawSize) - (DWORD)(&allocateAddr[szRawSize + sizeof(tarCal)]) - sizeof(retJmp);
			memcpy(&retJmp[1], &relativeAddr, sizeof(DWORD));
			memcpy(&allocateAddr[szRawSize + sizeof(tarCal)], retJmp, sizeof(retJmp));

			return TRUE;
		}
		else
		{
			MessageBoxW(NULL, L"SetHook Failed!!", NULL, NULL);
			return FALSE;
		}
	}

	DWORD MemX::MemSearch(DWORD dwBeginAddr, PBYTE aSearchCode, SIZE_T szCode, BOOL isBackward)
	{
		for (; ; )
		{
			if (dwBeginAddr < 0x7FFF0000 && dwBeginAddr > 0x00010000)
			{
				//DWORD oldProtect = 0;
				//VirtualProtect((LPVOID)beginAddr, lenOfCode, PAGE_EXECUTE_READWRITE, &oldProtect);
				if (!memcmp(aSearchCode, (void*)dwBeginAddr, szCode))
				{
					return dwBeginAddr;
				}

				if (isBackward)
				{
					dwBeginAddr++;
				}
				else
				{
					dwBeginAddr--;
				}
			}
			else
			{
				return 0;
			}
		}
	}
}


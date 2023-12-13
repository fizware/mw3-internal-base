#include "stdafx.h"
#include "sdk.h"
#include "xor.hpp"
#include "lazyimporter.h"
#include "memory.h"
#include <map>
#include "defs.h"
#include "globals.h"
#include "xorstr.hpp"
#include "weapon.h"
#pragma comment(lib, "user32.lib")
#define DEBASE(a) ((size_t)a - (size_t)(unsigned long long)GetModuleHandleA(NULL))

uintptr_t dwProcessBase;
uint64_t backup = 0, Online_Loot__GetItemQuantity = 0, stackFix = 0;
NTSTATUS(*NtContinue)(PCONTEXT threadContext, BOOLEAN raiseAlert) = nullptr;

DWORD64 resolveRelativeAddress(DWORD64 instr, DWORD offset, DWORD instrSize) {
	return instr == 0ui64 ? 0ui64 : (instr + instrSize + *(int*)(instr + offset));
}

bool compareByte(const char* pData, const char* bMask, const char* szMask) {
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD64 findPattern(DWORD64 dwAddress, DWORD64 dwLen, const char* bMask, const char* szMask) {
	DWORD length = (DWORD)strlen(szMask);
	for (DWORD i = 0; i < dwLen - length; i++)
		if (compareByte((const char*)(dwAddress + i), bMask, szMask))
			return (DWORD64)(dwAddress + i);
	return 0ui64;
}

LONG WINAPI TopLevelExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	if (pExceptionInfo && pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION)
	{
		if (pExceptionInfo->ContextRecord->R11 == 0xDEEDBEEF89898989)
		{
			pExceptionInfo->ContextRecord->R11 = backup;

			if (pExceptionInfo->ContextRecord->Rip > Online_Loot__GetItemQuantity && pExceptionInfo->ContextRecord->Rip < (Online_Loot__GetItemQuantity + 0x1000))
			{
				pExceptionInfo->ContextRecord->Rip = stackFix;
				pExceptionInfo->ContextRecord->Rax = 1;
			}
			NtContinue(pExceptionInfo->ContextRecord, 0);
		}
	}

	return EXCEPTION_CONTINUE_SEARCH;
}


namespace process
{
	HWND hwnd;

	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam)
	{
		DWORD dwPid = 0;
		GetWindowThreadProcessId(hWnd, &dwPid);
		if (dwPid == lParam)
		{
			hwnd = hWnd;
			return FALSE;
		}
		return TRUE;
	}

	HWND get_process_window()
	{
		if (hwnd)
			return hwnd;

		EnumWindows(EnumWindowCallBack, GetCurrentProcessId());

		if (hwnd == NULL)
			Exit();

		return hwnd;
	}
}

template<typename T> inline auto readMemory(uintptr_t ptr) noexcept -> T {
	if (is_bad_ptr(ptr)) {
		//DEBUG_INFO("Attempted to read invalid memory at {:#x}", ptr);
		return {};
	}
	return *reinterpret_cast<T*>(ptr);
}
template<typename T> inline auto writeMemory(uintptr_t ptr, T value) noexcept -> T {
	if (is_bad_ptr(ptr)) {
		//DEBUG_INFO("Attempted to read invalid memory at {:#x}", ptr);
		return {};
	}
	return *reinterpret_cast<T*>(ptr) = value;
}


namespace g_data
{
	uintptr_t base;
	uintptr_t peb;
	HWND hWind;
	void init()
	{
		base = (uintptr_t)(iat(GetModuleHandleA).get()("cod.exe"));


		hWind = process::get_process_window();

		peb = __readgsqword(0x60);



		/*	globals::unlockallbase = PatternScanEx(base + 0x5000000, 0x4F00000, xorstr_("\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\xC8\xC5\xF0\x57\xC9\xC4\xE1\xF3\x2A\xC9\x48\x8B\xCF\xE8\x00\x00\x00\x00\x48\x8B\x5C\x24\x00\xB8\x00\x00\x00\x00\x48\x83\xC4\x20\x5F\xC3"), xorstr_("xxx????x????xxxxxxxxxxxxxxx????xxxx?x????xxxxxx")) - base;
			globals::unlockallbase = globals::unlockallbase + 0x7;
			memcpy((BYTE*)(globals::UnlockBytes), (BYTE*)g_data::base + globals::unlockallbase, 5);
			globals::checkbase = FindOffset(base + 0x2000000, 0x1F00000, xorstr_("\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x75\x10\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x84\xC0\x74\x0F"), xorstr_("xxx????x????xxxxxxx????x????xxxx"), 3, 7, 0);
			globals::checkbase = globals::checkbase + -0x8;*/
	}
}

#pragma once
#include "framework.h"
#include "cfg.h"
#include "address.h"

#define ADD_ADDRESS( name, mod_name, sig ) address_t name =  utility::find_ida_sig( mod_name, sig )
#define ADD_ADDRESS_FUNCTION( name, func ) address_t name =  func( );


namespace utility
{
	DWORD GetProcId(const char* procName);
	HMODULE GetModuleHandleSafe(const char* pszModuleName);
	uintptr_t PatternScan(const char* sig, const char* mask, uintptr_t begin, unsigned int size);
	uintptr_t PatternScanEx(HANDLE hProcess, uintptr_t start, uintptr_t size, const char* sig, const char* mask);
	uintptr_t FindOffset(const char* sig, const char* mask, uintptr_t begin, unsigned int size, uintptr_t base_offset, uintptr_t pre_base_offset, uintptr_t rindex, bool addRip = true);
	address_t find_ida_sig(const char* mod, const char* sig);
	address_t get_vfunc(address_t table, uint16_t index);
	uint32_t get_vtable_length(address_t table);
	uintptr_t GetMethod(uintptr_t table, const char* funcName);
}


#define NOINLINE __declspec( noinline )

#define MEMBER_FUNC_ARGS(...) ( this, __VA_ARGS__ ); }
#define VFUNC( index, func, sig ) auto func { return utility::get_vfunc( this, index ).cast< sig >() MEMBER_FUNC_ARGS
#define CUSTOM_VFUNC( func, sig, addr ) auto func { return addr.cast< sig >() MEMBER_FUNC_ARGS
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast< type* >( reinterpret_cast< uintptr_t >( this ) + offset.cast() ); }

namespace process
{
	inline HWND hwnd;
	BOOL CALLBACK EnumWindowCallBack(HWND hWnd, LPARAM lParam);
	HWND get_process_window();
	HWND get_process_window(DWORD procID);
}


static uintptr_t __cdecl I_beginthreadex(void* _Security, unsigned _StackSize, _beginthreadex_proc_type _StartAddress, void* _ArgList, unsigned _InitFlag, unsigned* _ThrdAddr) {
	return iat(_beginthreadex).get()(_Security, _StackSize, _StartAddress, _ArgList, _InitFlag, _ThrdAddr);
}
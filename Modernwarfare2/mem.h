#pragma once
#include "utility.h"
//#include "m3m0re.h"

#define ADD_INTERFACE( type, var_name, address ) type* var_name = address.cast< type* >();
#define ADD_INTERFACE_CUSTOM( type, var_name, function ) type* var_name = function();
#define ADD_ADDRESS( name, mod_name, sig ) address_t name =  utility::find_ida_sig( mod_name, sig )
#define ADD_ADDRESS_FUNCTION( name, func ) address_t name =  func( );

namespace ctx
{
		ADD_ADDRESS(trampoline, NULL, { "FF 23" });

	
		uintptr_t logonstatus = utility::find_ida_sig(NULL, XOR("40 53 48 83 ec 20 48 63 c1 ba ? ? ? ? 48 69 d8 ? ? ? ?"));

		uintptr_t swap_chain = utility::find_ida_sig(NULL, XOR("48 8B 0D ? ? ? ? 33 D2 E8 ? ? ? ? 48 C7 05 ? ? ? ? 00 00 00 00 48 83 C4 ? C3")).self_jmp(0x3);

		uintptr_t command_queue = utility::find_ida_sig(NULL, XOR("8b c1 48 8d 0d ? ? ? ? 48 6b c0 78 48 03 c1 c3")).self_jmp(0x5);

	};
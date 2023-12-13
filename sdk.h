#pragma once
#include "stdafx.h"
#include "vec.h"


#define ror

#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)
#define BYTEn(x, n)   (*((BYTE*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)

//auto padding
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define is_valid_ptr(p) ((uintptr_t)(p) <= 0x7FFFFFFEFFFF && (uintptr_t)(p) >= 0x1000) 
#define is_bad_ptr(p)	(!is_valid_ptr(p))

template <typename T>
bool IsValidPtr(PVOID ptr)
{
	if (is_bad_ptr(ptr))return false;
	else
		return true;

}


bool world(const Vector3& WorldPos, Vector2* ScreenPos);

//class cg_t
//{
//public:
//	char pad_0000[48]; //0x0000
//	Vector3 vecOrig; //0x0030
//	char pad_003C[416]; //0x003C
//	Vector3 viewAngle; //0x01DC
//	char pad_01E8[112]; //0x01E8
//	int32_t N0000009A; //0x0258
//	int32_t Health; //0x025C
//	char pad_0260[160]; //0x0260
//	int32_t N000000AF; //0x0300
//	int32_t Uav; //0x0304
//	char pad_0308[1408]; //0x0308
//}; //Size: 0x0888


//[<ModernWarfare.exe>+1760F190]
class N0000004E
{
public:
	char pad_0000[1144]; //0x0000
	char N00000A88[16]; //0x0478
	char pad_0488[32]; //0x0488
	char N00000A89[16]; //0x04A8
	char pad_04B8[19416]; //0x04B8
}; //Size: 0x5090
static_assert(sizeof(N0000004E) == 0x5090);

#define game_mode 0xFAA1AD0
namespace player_info
{
	constexpr auto local_index = 0x55570;
	constexpr auto local_index_pos = 0x02E4;
	constexpr auto size = 0x13D60;
	constexpr auto valid = 0x2C9;
	constexpr auto team_id = 0x0D58;
	constexpr auto position_ptr = 0xEA8;
	constexpr auto stance = 0x5C7C;
	constexpr auto recoil_offset = 0x9C930;
	constexpr auto dead_1 = 0x199C;
	constexpr auto dead_2 = 0x13A68;
	//constexpr auto loot_ptr = 0x1EA6A3F0;
	//constexpr auto weapon_index = 0x1008;
}

namespace bones
{
	constexpr auto bone_base_pos = 0x160838;
	constexpr auto size = 0x188;
	constexpr auto visible = 0x222DCB0;
	constexpr auto weapon_definitions = 0x12F05E70;
	//constexpr auto loot_ptr = 0x1EA6A3F0;
	constexpr auto distribute = 0xAECCA40;
}

namespace view_port
{
	constexpr auto refdef_ptr = 0x12F1AD70;
	constexpr auto camera_ptr = 0x1376EFF0;
	constexpr auto camera_view_x = 0x108;
	constexpr auto camera_view_y = 0x118;
	constexpr auto camera_view_z = 0x128;
	constexpr auto camera_pos = 0x0204;
	//    constexpr auto loot_ptr = 0x1EA6A3F0;
}

namespace client
{
	//constexpr auto info_ptr = 0x17E24638; //client_info
	//constexpr auto base_offset = 0x9ED78; //client_Base
	constexpr auto name_array = 0x12F1AD38;
	constexpr auto name_array_padding = 0x2C80;
	//constexpr auto loot_ptr = 0x1E91EC90;
}

namespace direcX
{
	//    constexpr uint32_t command_queue = 0x20B808D8;
}

//////////////////////////////////////////////////////////


namespace g_data
{
	extern HWND hWind;
	extern uintptr_t base;
	extern uintptr_t peb;
	extern uintptr_t visible_base;
	extern uintptr_t unlocker;
	extern uintptr_t ddl_loadasset;
	extern uintptr_t ddl_getrootstate;
	extern uintptr_t ddl_getdllbuffer;
	extern uintptr_t ddl_movetoname;
	extern uintptr_t ddl_setint;
	extern uintptr_t Dvar_FindVarByName;
	extern uintptr_t Dvar_SetBoolInternal;
	extern uintptr_t Dvar_SetInt_Internal;
	extern uintptr_t Dvar_SetFloat_Internal;
	extern uintptr_t Camo_Offset_Auto_Test;


	extern uintptr_t Clantag_auto;

	extern uintptr_t a_parse;
	extern uintptr_t ddl_setstring;
	extern uintptr_t ddl_movetopath;
	extern uintptr_t ddlgetInth;
	extern QWORD current_visible_offset;
	extern QWORD cached_visible_base;
	extern QWORD last_visible_offset;
	extern uintptr_t cached_client_t;
	void init();

}
union DvarValue
{
	bool enabled;
	int32_t integer;
	uint32_t unsignedInt;
	float value;
	Vector4 vector;
	const char* string;
	unsigned __int8 color[4];
	uint64_t unsignedInt64;
	int64_t integer64;
};

typedef enum DvarType : uint8_t
{
	DVAR_TYPE_BOOL = 0x0,
	DVAR_TYPE_FLOAT = 0x1,
	DVAR_TYPE_FLOAT_2 = 0x2,
	DVAR_TYPE_FLOAT_3 = 0x3,
	DVAR_TYPE_FLOAT_4 = 0x4,
	DVAR_TYPE_INT = 0x5,
	DVAR_TYPE_INT64 = 0x6,
	DVAR_TYPE_UINT64 = 0x7,
	DVAR_TYPE_ENUM = 0x8,
	DVAR_TYPE_STRING = 0x9,
	DVAR_TYPE_COLOR = 0xA,
	DVAR_TYPE_FLOAT_3_COLOR = 0xB,
	DVAR_TYPE_COUNT = 0xC,
} DvarType;

struct dvar_s
{
	char name[4];
	uint32_t flags;
	BYTE level[1];
	DvarType type;
	bool modified;
	uint32_t checksum;
	char* description;
	char pad2[16];
	unsigned __int16 hashNext;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;

};
class cg_t
{
public:
	char pad_0000[48]; //0x0000
	Vector3 vecOrig; //0x0030
	char pad_003C[416]; //0x003C
	Vector3 viewAngle; //0x01DC
	char pad_01E8[112]; //0x01E8
	int32_t N0000009A; //0x0258
	int32_t Health; //0x025C
	char pad_0260[160]; //0x0260
	int32_t N000000AF; //0x0300
	int32_t Uav; //0x0304
	char pad_0308[1408]; //0x0308
}; //Size: 0x0888
static_assert(sizeof(cg_t) == 0x888);


namespace radarVars
{
	extern bool transparent;
	extern bool bEnable2DRadar;
	extern bool bSetRadarSize;
	extern int iScreenWidth;
	extern int iScreenHeight;
	extern ImVec2 v2RadarNormalLocation;
	extern ImVec2 v2RadarNormalSize;
	extern ImVec2 v2SetRadarSize;
	extern ImDrawList* Draw;
}

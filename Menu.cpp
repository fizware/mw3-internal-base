#include "stdafx.h"
#include "Menu.h"
#include "imgui/imgui.h"
# include "globals.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx12.h"
#include "obfuscator.hpp"
#include "xor.hpp"
#include"memory.h"
#include "mem.h"
#include "xorstr.hpp"
#include "style.h"
#include <Kiero/kiero.h>
#include "CProjectSDK.hpp"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
bool b_menu_open = false;
bool b_hook_init = true;
bool b_debug_open = false;
bool boxcheck;
int Selected_Camo_MW = 0;
int Selected_Camo_CW = 0;
int Selected_Camo_VG = 0;
int gameMode2 = 0;
int i_MenuTab = 0;
uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets)
{
	if (ptr != 0)
	{
		uintptr_t addr = ptr;
		for (unsigned int i = 0; i < offsets.size(); ++i)
		{
			addr = *(uintptr_t*)addr;
			addr += offsets[i];
		}
		return addr;
	}
	else
		return 0;
}


//uint64_t BASEIMAGE2 = reinterpret_cast<uint64_t>(GetModuleHandleA(NULL));

bool b_fov = false;
float f_fov = 1.20f;
float f_map = 1.0f;
bool b_map = false;
bool b_brightmax = false;
bool b_thirdperson = false;
bool b_heartcheat = false;
bool b_norecoil = false;
bool b_no_flashbang = false;

struct unnamed_type_integer
{
	int min;
	int max;
};
struct unnamed_type_integer64
{
	__int64 min;
	__int64 max;
};
struct unnamed_type_enumeration
{
	int stringCount;
	const char* strings;
};
/* 433 */
struct unnamed_type_unsignedInt64
{
	unsigned __int64 min;
	unsigned __int64 max;
};

/* 434 */
struct unnamed_type_value
{
	float min;
	float max;
	float devguiStep;
};

/* 435 */
struct unnamed_type_vector
{
	float min;
	float max;
	float devguiStep;
};




uintptr_t cbuff1;
uintptr_t cbuff2;
char inputtext[50];
int C_TagMOde = 0;


__int64 find_pattern(__int64 range_start, __int64 range_end, const char* pattern) {
	const char* pat = pattern;
	__int64 firstMatch = NULL;
	__int64 pCur = range_start;
	__int64 region_end;
	MEMORY_BASIC_INFORMATION mbi{};
	while (sizeof(mbi) == VirtualQuery((LPCVOID)pCur, &mbi, sizeof(mbi))) {
		if (pCur >= range_end - strlen(pattern))
			break;
		if (!(mbi.Protect & (PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_READWRITE))) {
			pCur += mbi.RegionSize;
			continue;
		}
		region_end = pCur + mbi.RegionSize;
		while (pCur < region_end)
		{
			if (!*pat)
				return firstMatch;
			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
				if (!firstMatch)
					firstMatch = pCur;
				if (!pat[1] || !pat[2])
					return firstMatch;

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;
				else
					pat += 2;
			}
			else {
				if (firstMatch)
					pCur = firstMatch;
				pat = pattern;
				firstMatch = 0;
			}
			pCur++;
		}
	}
	return NULL;
}


bool init_once = true;
char input[30];
bool Unlock_once = true;

void Visual()
{
	
}
void KeyBindButton(int& key, int width, int height)
{
	
}

void Aimbot()
{

}
void ColorPicker()
{
	

}

void Misc()
{

}



namespace g_menu
{
	auto Center(float availableWidth, float elementWidth, float padding = 0) -> void const {
		ImGui::SameLine(((availableWidth / 2) - (elementWidth / 2)) + padding);
	}


	void menu()
	{
		if (b_hook_init) {
			ImGui::SetNextWindowSize(ImVec2(200, 75), ImGuiCond_Always);
			ImGui::SetNextWindowPos(ImVec2(18, 23));
			ImGui::Begin(xorstr_("Fizware"), &b_hook_init, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);
			Center(165, ImGui::CalcTextSize("CodeCave").x);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);
			ImGui::TextColored(IColor::Violet(), "CodeCave");
			ImGui::SameLine(0, 0);
			ImGui::Text(".hook");
			ImGui::Separator();
			ImGui::SetWindowFontScale(0.9f); 
			ImGui::Text("Hook Initialized, Open Menu!");
			ImGui::SetWindowFontScale(1.0f); 
			ImGui::End();

		}
		if (GetAsyncKeyState(VK_INSERT) & 0x1)
		{
			b_menu_open = !b_menu_open;
			b_hook_init = false;

		}
		if (init_once)
		{
			//init_buffer();
			ImGui::SetNextWindowPos(ImVec2(200, 200));
			init_once = false;
		}
		if (GetAsyncKeyState(VK_END) & 1)
			kiero::shutdown();
		if (b_menu_open && screenshot::visuals)
		{
			ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Always);

			ImGui::Begin(xorstr_("abc"), &b_menu_open, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
			//ImGui::Begin(xorstr_("MENU"), &b_menu_open, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);

			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 3;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
			ImGui::Dummy(ImVec2(0.0f, 1.0f));
			for (int i = 0; i < 25; i++)
			{
				ImGui::Spacing();
				ImGui::SameLine();
			}


			ImGui::Dummy(ImVec2(0.0f, 3.0f));
			ImGui::SetWindowPos(ImVec2(dwWidth * 2.0f, dwHeight * 0.2f), ImGuiCond_Once);
			ImGui::EndChild();
		}

	}
}
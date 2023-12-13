#include "globals.h"
#include "sdk.h"

namespace globals
{
	UINT64 checkbase;
	int theme = 0;
	bool b_box = false;

}

namespace color
{
	ImColor Color{ 255,255,255,255 };
	ImColor VisibleColorTeam{ 0.f, 0.f, 1.f, 1.f };
	ImColor NotVisibleColorTeam{ 0.f, 0.75f, 1.f, 1.f };
	ImColor VisibleColorEnemy{ 0.33f, 0.97f, 0.35f, 1.00f };
	ImColor NotVisibleColorEnemy{ 0.97f, 0.01f, 0.01f, 1.00f };
	ImColor bfov{ 0.97f, 0.01f, 0.01f, 1.00f };
	ImColor draw_crosshair{ 0.f, 0.75f, 1.f, 1.f };
	ImColor nameColor{ 255,255,0,255 };
	ImColor dis_Color{ 255,255,0,255 };
	ImColor healthbar{ 0.f, 0.f, 1.f, 1.f };
}

namespace screenshot
{
	 bool visuals = true;
	 bool* pDrawEnabled = nullptr;
		uint32_t screenshot_counter = 0;
		uint32_t  bit_blt_log = 0;
	 const char* bit_blt_fail;
	 uintptr_t  bit_blt_anotherlog;

		uint32_t	GdiStretchBlt_log = 0;
	 const char* GdiStretchBlt_fail;
	 uintptr_t  GdiStretchBlt_anotherlog;

	uintptr_t	texture_copy_log = 0;




	 uintptr_t virtualqueryaddr = 0;
}



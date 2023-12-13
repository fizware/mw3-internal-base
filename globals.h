#pragma once
#include "stdafx.h"
#include "sdk.h"
#define M_PI   3.141592654f
namespace globals
{

}


namespace color
{
	extern ImColor Color;
	extern ImColor VisibleColorTeam;
	extern ImColor NotVisibleColorTeam;
	extern ImColor VisibleColorEnemy;
	extern ImColor NotVisibleColorEnemy;
	extern ImColor bfov;
	extern ImColor draw_crosshair;
	extern ImColor nameColor;
	extern ImColor dis_Color;
	extern ImColor healthbar;
}

namespace screenshot
{
	extern bool visuals ;
	extern bool* pDrawEnabled;
	extern	uint32_t screenshot_counter;
	extern	uint32_t  bit_blt_log;
	extern const char* bit_blt_fail;
	extern uintptr_t  bit_blt_anotherlog;

	extern	uint32_t	GdiStretchBlt_log;
	extern const char* GdiStretchBlt_fail;
	extern uintptr_t  GdiStretchBlt_anotherlog;

	extern	uintptr_t	texture_copy_log;




	extern uintptr_t virtualqueryaddr;
}



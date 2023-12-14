#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H
#include "framework.h"
#include "color.h"
#include "config.h"

ADD_CONFIG_ITEM(imageBase, uintptr_t, 0);

ADD_CONFIG_ITEM(showmenu, bool, false);

typedef struct _globals_vars
{
	uintptr_t baseModule;
	DWORD procID;
	HWND hWind;
	HANDLE hProc;
} global_vars;

extern global_vars* g_vars;

#endif // !GLOBAL_H

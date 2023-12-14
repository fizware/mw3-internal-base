#include "dllmain.h"
#include "input.h"
#include <sys/stat.h>

extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, code, wParam, lParam); }

#define StartThread(mainThread, dllhandle) I_beginthreadex(0, 0, (_beginthreadex_proc_type)mainThread, dllhandle, 0, 0);


__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ori_present(pSwapChain, SyncInterval, Flags);
	if (d3d12::pCommandQueue == nullptr)
	{
		ori_present(pSwapChain, SyncInterval, Flags);
	}

	DXGI_SWAP_CHAIN_DESC sdesc;
	pSwapChain->GetDesc(&sdesc);

	if (sdesc.OutputWindow == GetForegroundWindow())
	{
		ImFont* main_font = imgui::start(
			reinterpret_cast<IDXGISwapChain3*>(*(uintptr_t*)(ctx::swap_chain)),
			reinterpret_cast<ID3D12CommandQueue*>(*(uintptr_t*)(ctx::command_queue)), nullptr, 16);

		imgui::imgui_frame_header();

		if (GetAsyncKeyState(VK_HOME) & 1)
			showmenu = !showmenu;

		if (showmenu)
		{
			ImGui::GetIO().MouseDrawCursor;
			menu->Menu();
		}

		ImGuiStyle& style = ImGui::GetStyle();
		const float bor_size = style.WindowBorderSize;
		style.WindowBorderSize = 0.0f;
		style.WindowBorderSize = bor_size;

		imgui::imgui_frame_end();
	}
	return ori_present(pSwapChain, SyncInterval, Flags);
}

int GetLogonStatus(int status) {
	return reinterpret_cast<int(*)(int)>(ctx::logonstatus)(status);
}

void Initialize()
{
	g_vars = new global_vars();
	imageBase = (QWORD)(iat(GetModuleHandleA).get()("cod.exe"));

	while (GetLogonStatus(0) != 2)
	{
		std::this_thread::sleep_for(
			std::chrono::milliseconds(5));
	}

	g_vars->procID = utility::GetProcId("cod.exe");
	g_vars->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, g_vars->procID);
	g_vars->hWind = process::get_process_window();

	
}

bool init = false;
DWORD WINAPI  initthread(HMODULE hModule)
{
	
		Initialize();
		LOGS_ADDR(imageBase);
		LOGS_ADDR(ctx::trampoline);
		LOGS_ADDR(ctx::swap_chain);
		LOGS_ADDR(ctx::command_queue);
		
		
		if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success)
		{
			kiero::bind(54, (void**)&oExecuteCommandListsD3D12, imgui::hookExecuteCommandListsD3D12);
			kiero::bind(140, (void**)&ori_present, present_hk);
		}
		CreateDirectoryA(fmt::format("C:\\{}", misc::generate_unique_random_string(CT_HASH("UC"), 20)).c_str(), NULL);
		std::string cfg = fmt::format("C:\\{}\\R-{}", misc::generate_unique_random_string(CT_HASH("UC"), 20), misc::generate_unique_random_string(CT_HASH("Config"), 20));
		config::set_config_directory(cfg);
		config::load(XOR("profile_1"));
	return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		StartThread(initthread, module);
		//initthread(module);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		
		break;
	}
	return TRUE;
}
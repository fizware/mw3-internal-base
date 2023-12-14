#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "framework.h"
#include "cfg.h"
#include "utility.h"
#include "menu.h"
#include "mem.h"
#include "mem_protect.h"
#include "imgui_draw_api.h"
#include "font_logo.h"
#include "inter.h"
#include "dm_serif.h"
#include "stb_image.h"
#include "fmt/format.h"
#include "hash.h"
#include "misc.h"
#include "config.h"



using namespace std;
global_vars* g_vars;
cMenu* menu;

typedef LRESULT(CALLBACK* tWndProc)(HWND hWnd, UINT Msg, WPARAM wp, LPARAM lp);
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void(*oExecuteCommandListsD3D12)(ID3D12CommandQueue*, UINT, ID3D12CommandList*);
typedef long(__fastcall* Present)(IDXGISwapChain*, UINT, UINT);
static Present ori_present = NULL;

void Initialize();

namespace ogr_function
{
	tWndProc WndProc;
}

LRESULT __stdcall hkWndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	bool hHandel = true;
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	if (GetAsyncKeyState(VK_PRIOR) & 1)
	{
		kiero::shutdown();
		hHandel = false;
	}

	if (showmenu && io.WantCaptureMouse && io.WantCaptureKeyboard && (uMsg == WM_MOUSEHOVER || uMsg == WM_NCMOUSEHOVER || uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP || uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP || uMsg == WM_MOUSEWHEEL || uMsg == WM_MOUSEHWHEEL || uMsg == WM_MOUSEMOVE))
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		switch (uMsg)
		{
		case WM_SIZE:
			if (imgui::IsReady()) {
				imgui::clear();
				ImGui_ImplDX12_InvalidateDeviceObjects();
				imgui::reset_imgui_request();
			}
			break;
		}
	}
	return ogr_function::WndProc(hWnd, uMsg, wParam, lParam);
}


void WndProc_hk()
{
	ogr_function::WndProc = (WNDPROC)SetWindowLongPtrW(g_vars->hWind, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
}

namespace d3d12
{
	IDXGISwapChain3* pSwapChain;
	ID3D12Device* pDevice;
	ID3D12CommandQueue* pCommandQueue;
	ID3D12Fence* pFence;
	ID3D12DescriptorHeap* d3d12DescriptorHeapBackBuffers = nullptr;
	ID3D12DescriptorHeap* d3d12DescriptorHeapImGuiRender = nullptr;
	ID3D12DescriptorHeap* pSrvDescHeap = nullptr;
	ID3D12DescriptorHeap* pRtvDescHeap = nullptr;
	ID3D12GraphicsCommandList* pCommandList = nullptr;

	FrameContext* FrameContextArray;
	ID3D12Resource** pID3D12ResourceArray;
	D3D12_CPU_DESCRIPTOR_HANDLE* RenderTargetDescriptorArray;

	HANDLE hSwapChainWaitableObject;
	HANDLE hFenceEvent;

	UINT NUM_FRAMES_IN_FLIGHT;
	UINT NUM_BACK_BUFFERS;

	UINT   frame_index = 0;
	UINT64 fenceLastSignaledValue = 0;
}

void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
	if (!d3d12::pCommandQueue)
	{
		d3d12::pCommandQueue = queue;
		std::cout << "HOOKED!" << std::endl;
	}

	oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
}

namespace imgui
{
	bool is_ready;
	bool is_need_reset_imgui;

	bool IsReady()
	{
		return is_ready;
	}

	void reset_imgui_request()
	{
		is_need_reset_imgui = true;
	}

	__forceinline bool get_is_need_reset_imgui()
	{
		return is_need_reset_imgui;
	}

	void init_d3d12(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue)
	{
		d3d12::pSwapChain = pSwapChain;
		d3d12::pCommandQueue = pCommandQueue;

		if (!SUCCEEDED(d3d12::pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&d3d12::pDevice)))
			Exit();

		{
			DXGI_SWAP_CHAIN_DESC1 desc;

			if (!SUCCEEDED(d3d12::pSwapChain->GetDesc1(&desc)))
				Exit();

			d3d12::NUM_BACK_BUFFERS = desc.BufferCount;
			d3d12::NUM_FRAMES_IN_FLIGHT = desc.BufferCount;
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.NumDescriptors = d3d12::NUM_BACK_BUFFERS;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			desc.NodeMask = 1;

			if (!SUCCEEDED(d3d12::pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&d3d12::pRtvDescHeap))))
				Exit();
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			desc.NumDescriptors = 1;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
			desc.NodeMask = 0;

			if (!SUCCEEDED(d3d12::pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&d3d12::pSrvDescHeap))))
				Exit();
		}

		if (!SUCCEEDED(d3d12::pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&d3d12::pFence))))
			Exit();

		d3d12::FrameContextArray = new FrameContext[d3d12::NUM_FRAMES_IN_FLIGHT];
		d3d12::pID3D12ResourceArray = new ID3D12Resource * [d3d12::NUM_BACK_BUFFERS];
		d3d12::RenderTargetDescriptorArray = new D3D12_CPU_DESCRIPTOR_HANDLE[d3d12::NUM_BACK_BUFFERS];

		for (UINT i = 0; i < d3d12::NUM_FRAMES_IN_FLIGHT; ++i)
		{
			if (!SUCCEEDED(d3d12::pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&d3d12::FrameContextArray[i].CommandAllocator))))
				Exit();
		}

		SIZE_T nDescriptorSize = d3d12::pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = d3d12::pRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

		for (UINT i = 0; i < d3d12::NUM_BACK_BUFFERS; ++i)
		{
			d3d12::RenderTargetDescriptorArray[i] = rtvHandle;
			rtvHandle.ptr += nDescriptorSize;
		}

		if (!SUCCEEDED(d3d12::pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, d3d12::FrameContextArray[0].CommandAllocator, NULL, IID_PPV_ARGS(&d3d12::pCommandList))) ||
			!SUCCEEDED(d3d12::pCommandList->Close()))
		{
			Exit();
		}

		d3d12::hSwapChainWaitableObject = d3d12::pSwapChain->GetFrameLatencyWaitableObject();

		d3d12::hFenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

		if (d3d12::hFenceEvent == NULL)
			Exit();

		ID3D12Resource* pBackBuffer;
		for (UINT i = 0; i < d3d12::NUM_BACK_BUFFERS; ++i)
		{
			if (!SUCCEEDED(d3d12::pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer))))
				Exit();

			d3d12::pDevice->CreateRenderTargetView(pBackBuffer, NULL, d3d12::RenderTargetDescriptorArray[i]);
			d3d12::pID3D12ResourceArray[i] = pBackBuffer;
		}
	}

	void _clear()
	{
		d3d12::pSwapChain = nullptr;
		d3d12::pDevice = nullptr;
		d3d12::pCommandQueue = nullptr;

		if (d3d12::pFence)
		{
			d3d12::pFence->Release();
			d3d12::pFence = nullptr;
		}

		if (d3d12::pSrvDescHeap)
		{
			d3d12::pSrvDescHeap->Release();
			d3d12::pSrvDescHeap = nullptr;
		}

		if (d3d12::pRtvDescHeap)
		{
			d3d12::pRtvDescHeap->Release();
			d3d12::pRtvDescHeap = nullptr;
		}

		if (d3d12::pCommandList)
		{
			d3d12::pCommandList->Release();
			d3d12::pCommandList = nullptr;
		}

		if (d3d12::FrameContextArray)
		{
			for (UINT i = 0; i < d3d12::NUM_FRAMES_IN_FLIGHT; ++i)
			{
				if (d3d12::FrameContextArray[i].CommandAllocator)
				{
					d3d12::FrameContextArray[i].CommandAllocator->Release();
					d3d12::FrameContextArray[i].CommandAllocator = nullptr;
				}
			}

			delete[] d3d12::FrameContextArray;
			d3d12::FrameContextArray = NULL;
		}

		if (d3d12::pID3D12ResourceArray)
		{
			for (UINT i = 0; i < d3d12::NUM_BACK_BUFFERS; ++i)
			{
				if (d3d12::pID3D12ResourceArray[i])
				{
					d3d12::pID3D12ResourceArray[i]->Release();
					d3d12::pID3D12ResourceArray[i] = nullptr;
				}
			}

			delete[] d3d12::pID3D12ResourceArray;
			d3d12::pID3D12ResourceArray = NULL;
		}

		if (d3d12::RenderTargetDescriptorArray)
		{
			delete[] d3d12::RenderTargetDescriptorArray;
			d3d12::RenderTargetDescriptorArray = NULL;
		}

		if (d3d12::hSwapChainWaitableObject)
		{
			d3d12::hSwapChainWaitableObject = nullptr;
		}

		if (d3d12::hFenceEvent)
		{
			CloseHandle(d3d12::hFenceEvent);
			d3d12::hFenceEvent = nullptr;
		}

		d3d12::NUM_FRAMES_IN_FLIGHT = 0;
		d3d12::NUM_BACK_BUFFERS = 0;

		d3d12::frame_index = 0;
	}

	void clear()
	{
		if (d3d12::FrameContextArray)
		{
			FrameContext* frameCtxt = &d3d12::FrameContextArray[d3d12::frame_index % d3d12::NUM_FRAMES_IN_FLIGHT];

			UINT64 fenceValue = frameCtxt->FenceValue;

			if (fenceValue == 0)
				return; // No fence was signaled

			frameCtxt->FenceValue = 0;

			bool bNotWait = d3d12::pFence->GetCompletedValue() >= fenceValue;

			if (!bNotWait)
			{
				d3d12::pFence->SetEventOnCompletion(fenceValue, d3d12::hFenceEvent);

				WaitForSingleObject(d3d12::hFenceEvent, INFINITE);
			}

			_clear();
		}
	}

	FrameContext* WaitForNextFrameResources()
	{
		UINT nextFrameIndex = d3d12::frame_index + 1;
		d3d12::frame_index = nextFrameIndex;

		HANDLE waitableObjects[] = { d3d12::hSwapChainWaitableObject, NULL };
		constexpr DWORD numWaitableObjects = 1;

		FrameContext* frameCtxt = &d3d12::FrameContextArray[nextFrameIndex % d3d12::NUM_FRAMES_IN_FLIGHT];

		WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

		return frameCtxt;
	}

	void reinit(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue)
	{
		init_d3d12(pSwapChain, pCommandQueue);
		ImGui_ImplDX12_CreateDeviceObjects();
	}

	bool LoadTextureFromMemory(unsigned char* buffer, int len, ID3D12Device* d3d_device, D3D12_CPU_DESCRIPTOR_HANDLE srv_cpu_handle, ID3D12Resource** out_tex_resource, int* out_width, int* out_height)
	{
		// Load from disk into a raw RGBA buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load_from_memory(buffer, len, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture resource
		D3D12_HEAP_PROPERTIES props;
		memset(&props, 0, sizeof(D3D12_HEAP_PROPERTIES));
		props.Type = D3D12_HEAP_TYPE_DEFAULT;
		props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		D3D12_RESOURCE_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc.Alignment = 0;
		desc.Width = image_width;
		desc.Height = image_height;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		ID3D12Resource* pTexture = NULL;
		d3d_device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
			D3D12_RESOURCE_STATE_COPY_DEST, NULL, IID_PPV_ARGS(&pTexture));

		// Create a temporary upload resource to move the data in
		UINT uploadPitch = (image_width * 4 + D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u) & ~(D3D12_TEXTURE_DATA_PITCH_ALIGNMENT - 1u);
		UINT uploadSize = image_height * uploadPitch;
		desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		desc.Alignment = 0;
		desc.Width = uploadSize;
		desc.Height = 1;
		desc.DepthOrArraySize = 1;
		desc.MipLevels = 1;
		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		desc.Flags = D3D12_RESOURCE_FLAG_NONE;

		props.Type = D3D12_HEAP_TYPE_UPLOAD;
		props.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		props.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

		ID3D12Resource* uploadBuffer = NULL;
		HRESULT hr = d3d_device->CreateCommittedResource(&props, D3D12_HEAP_FLAG_NONE, &desc,
			D3D12_RESOURCE_STATE_GENERIC_READ, NULL, IID_PPV_ARGS(&uploadBuffer));
		IM_ASSERT(SUCCEEDED(hr));

		// Write pixels into the upload resource
		void* mapped = NULL;
		D3D12_RANGE range = { 0, uploadSize };
		hr = uploadBuffer->Map(0, &range, &mapped);
		IM_ASSERT(SUCCEEDED(hr));
		for (int y = 0; y < image_height; y++)
			memcpy((void*)((uintptr_t)mapped + y * uploadPitch), image_data + y * image_width * 4, image_width * 4);
		uploadBuffer->Unmap(0, &range);

		// Copy the upload resource content into the real resource
		D3D12_TEXTURE_COPY_LOCATION srcLocation = {};
		srcLocation.pResource = uploadBuffer;
		srcLocation.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
		srcLocation.PlacedFootprint.Footprint.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srcLocation.PlacedFootprint.Footprint.Width = image_width;
		srcLocation.PlacedFootprint.Footprint.Height = image_height;
		srcLocation.PlacedFootprint.Footprint.Depth = 1;
		srcLocation.PlacedFootprint.Footprint.RowPitch = uploadPitch;

		D3D12_TEXTURE_COPY_LOCATION dstLocation = {};
		dstLocation.pResource = pTexture;
		dstLocation.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
		dstLocation.SubresourceIndex = 0;

		D3D12_RESOURCE_BARRIER barrier = {};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = pTexture;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;

		// Create a temporary command queue to do the copy with
		ID3D12Fence* fence = NULL;
		hr = d3d_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
		IM_ASSERT(SUCCEEDED(hr));

		HANDLE event = CreateEvent(0, 0, 0, 0);
		IM_ASSERT(event != NULL);

		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 1;

		ID3D12CommandQueue* cmdQueue = NULL;
		hr = d3d_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
		IM_ASSERT(SUCCEEDED(hr));

		ID3D12CommandAllocator* cmdAlloc = NULL;
		hr = d3d_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
		IM_ASSERT(SUCCEEDED(hr));

		ID3D12GraphicsCommandList* cmdList = NULL;
		hr = d3d_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc, NULL, IID_PPV_ARGS(&cmdList));
		IM_ASSERT(SUCCEEDED(hr));

		cmdList->CopyTextureRegion(&dstLocation, 0, 0, 0, &srcLocation, NULL);
		cmdList->ResourceBarrier(1, &barrier);

		hr = cmdList->Close();
		IM_ASSERT(SUCCEEDED(hr));

		// Execute the copy
		cmdQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&cmdList);
		hr = cmdQueue->Signal(fence, 1);
		IM_ASSERT(SUCCEEDED(hr));

		// Wait for everything to complete
		fence->SetEventOnCompletion(1, event);
		WaitForSingleObject(event, INFINITE);

		// Tear down our temporary command queue and release the upload resource
		cmdList->Release();
		cmdAlloc->Release();
		cmdQueue->Release();
		CloseHandle(event);
		fence->Release();
		uploadBuffer->Release();

		// Create a shader resource view for the texture
		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		d3d_device->CreateShaderResourceView(pTexture, &srvDesc, srv_cpu_handle);

		// Return results
		*out_tex_resource = pTexture;

		if (out_width)
			*out_width = image_width;

		if (out_height)
			*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}

	bool load_texture(unsigned char* buffer, int len, ID3D12Device* d3d_device, D3D12_CPU_DESCRIPTOR_HANDLE srv_cpu_handle, int* out_width, int* out_height)
	{
		ID3D12Resource* my_texture = NULL;
		bool ret = imgui::LoadTextureFromMemory(logohxd, sizeof(logohxd), d3d12::pDevice, srv_cpu_handle, &my_texture, out_width, out_height);
		IM_ASSERT(ret);
		return ret;
	}

	std::vector< ImTextureID > Logo_images = {};
	bool init_Texture = true;

	ImFont* start(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue, type::tImguiStyle SetStyleFunction, float font_size)
	{
		static ImFont* s_main_font = nullptr;
		if (is_ready && get_is_need_reset_imgui())
		{
			reinit(pSwapChain, pCommandQueue);

			is_need_reset_imgui = false;
		}

		if (is_ready)
			return s_main_font;

		init_d3d12(pSwapChain, pCommandQueue);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (SetStyleFunction == nullptr)
			ImGui::StyleColorsDark();
		else
			SetStyleFunction();

		ImGui_ImplWin32_Init(g_vars->hWind);
		ImGui_ImplDX12_Init(d3d12::pDevice, d3d12::NUM_FRAMES_IN_FLIGHT, DXGI_FORMAT_R8G8B8A8_UNORM, d3d12::pSrvDescHeap, d3d12::pSrvDescHeap->GetCPUDescriptorHandleForHeapStart(), d3d12::pSrvDescHeap->GetGPUDescriptorHandleForHeapStart());
		
		ImFont* main_font = io.Fonts->AddFontFromMemoryTTF(dm_serif, sizeof(dm_serif), font_size, nullptr, io.Fonts->GetGlyphRangesCyrillic());
		
		if (main_font == nullptr)
			Exit();

		WndProc_hk();

		s_main_font = main_font;

		is_ready = true;

		return s_main_font;
	}

	void imgui_frame_header()
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void imgui_no_border(type::tESP esp_function, ImFont* font)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		const float bor_size = style.WindowBorderSize;
		style.WindowBorderSize = 0.0f;
		esp_function(font);
		style.WindowBorderSize = bor_size;
	}

	void imgui_frame_end()
	{
		FrameContext* frameCtxt = WaitForNextFrameResources();
		UINT backBufferIdx = d3d12::pSwapChain->GetCurrentBackBufferIndex();

		{
			frameCtxt->CommandAllocator->Reset();
			static D3D12_RESOURCE_BARRIER barrier = {};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.pResource = d3d12::pID3D12ResourceArray[backBufferIdx];
			d3d12::pCommandList->Reset(frameCtxt->CommandAllocator, NULL);
			d3d12::pCommandList->ResourceBarrier(1, &barrier);
			d3d12::pCommandList->OMSetRenderTargets(1, &d3d12::RenderTargetDescriptorArray[backBufferIdx], FALSE, NULL);
			d3d12::pCommandList->SetDescriptorHeaps(1, &d3d12::pSrvDescHeap);
		}

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), d3d12::pCommandList);

		static D3D12_RESOURCE_BARRIER barrier = { };
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.pResource = d3d12::pID3D12ResourceArray[backBufferIdx];

		d3d12::pCommandList->ResourceBarrier(1, &barrier);
		d3d12::pCommandList->Close();

		d3d12::pCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*)&d3d12::pCommandList);

		//HRESULT results = ori_present(pSwapChain, SyncInterval, Flags);

		UINT64 fenceValue = d3d12::fenceLastSignaledValue + 1;
		d3d12::pCommandQueue->Signal(d3d12::pFence, fenceValue);
		d3d12::fenceLastSignaledValue = fenceValue;
		frameCtxt->FenceValue = fenceValue;
	}

	void hookExecuteCommandListsD3D12(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
		if (!d3d12::pCommandQueue)
		{
			d3d12::pCommandQueue = queue;

			LOGS("HOOKED");
		}

		oExecuteCommandListsD3D12(queue, NumCommandLists, ppCommandLists);
	}
}


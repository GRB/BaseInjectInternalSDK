#include "../../pch.h"

#if KIERO_INCLUDE_D3D11
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
Present o_present = nullptr;

ID3D11Device* device = nullptr;
ID3D11RenderTargetView* main_render_target_view;
ID3D11DeviceContext* context = nullptr;
WNDPROC o_wnd_proc;
DXGI_SWAP_CHAIN_DESC desc;

LRESULT __stdcall wnd_proc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	if (Globals::show_menu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}
	else {
		return CallWindowProc(o_wnd_proc, hWnd, uMsg, wParam, lParam);
	}
}

long __stdcall hk_present11(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags)
{
	if (static bool init = false; !init)
	{
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device))))
		{
			device->GetImmediateContext(&context);
			
			p_swap_chain->GetDesc(&desc);

			ID3D11Texture2D* p_back_buffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&p_back_buffer));
			_Post_ _Notnull_ device->CreateRenderTargetView(p_back_buffer, nullptr, &main_render_target_view);
			p_back_buffer->Release();
			o_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(desc.OutputWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wnd_proc)));

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantTextInput;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			ImGui_ImplWin32_Init(desc.OutputWindow);
			ImGui_ImplDX11_Init(device, context);
			ImGuiStylePicker::GoldBlack();

			init = true;
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Show the menu based on key press
	if (GetAsyncKeyState(Globals::menu_key) & 1) {
		Globals::show_menu = !Globals::show_menu;

		// FIND A WAY TO SHOW MOUSE, I DO WITH UNREALENGINE
		/*if (Globals::show_menu)
			Globals::lplayer->PlayerController->bShowMouseCursor = true;
		else
			Globals::lplayer->PlayerController->bShowMouseCursor = false;*/
	}

	// Operations of the menu
	im_gui_menu::operations();

	ImGui::EndFrame();
	ImGui::Render();

	context->OMSetRenderTargets(1, &main_render_target_view, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	//pSwapChain->Present(1, 0); // vsync
	//pSwapChain->Present(0, 0); // no vsync
	if (Globals::shutdown) {
		kiero::shutdown();
		device->Release();
		context->Release();
		p_swap_chain->Release();
		o_wnd_proc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(desc.OutputWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(o_wnd_proc)));
		o_present(p_swap_chain, sync_interval, flags);
		return 0;
	}

	return o_present(p_swap_chain, sync_interval, flags);
}

void impl::d3d11::init()
{
	assert(kiero::bind(8, reinterpret_cast<void**>(&o_present), hk_present11) == kiero::Status::Success);
}

#endif // KIERO_INCLUDE_D3D11
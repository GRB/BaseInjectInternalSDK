#include "pch.h"

#include "imguisettings.h"

uint64_t __stdcall main_loop(HMODULE h_module) {
    bool init_hook = false;

    AllocConsole();
    FILE* file = nullptr;
    freopen_s(&file, "CONOUT$", "w", stdout);

    // CG::InitSdk();

    while (!GetAsyncKeyState(Globals::panic_key))
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success && init_hook == false)
        {
            impl::d3d11::init();
            init_hook = true;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    fclose(file);
    fclose(stdout);
    FreeConsole();
    Globals::shutdown = true;
    Sleep(1000);
    FreeLibraryAndExitThread(h_module, 0);
}

BOOL APIENTRY DllMain(HMODULE h_module, uint64_t ul_reason_for_call, LPVOID lp_reserved) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        _Post_ _Notnull_ CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main_loop), h_module, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default: ;
    }
    return TRUE;
}
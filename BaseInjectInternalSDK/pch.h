#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS
#define UE4

#include <Windows.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <Psapi.h>
#include <thread>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <vector>

// Directx11 Headers Files
#include <dxgi.h>
#include <d3d11.h>
#include <d3dx9.h>

// Minhook Header File
#include "MinHook.h"

// Kiero Header Files
#include "Kiero/kiero.h"
#include "Kiero/impl/d3d11_impl.h"

// ImGui Header Files
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_win32.h"
#include "imgui/examples/imgui_impl_dx11.h"
#include "imgui_styles.h"
#include "imgui_menu.h"

#include "SDK.h"

#include "framework.h"

#endif
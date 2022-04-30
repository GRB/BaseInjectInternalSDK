#pragma once

namespace Globals {
	inline bool shutdown = false;
	inline const LPCWSTR gamewindowname = L""; //only needed for get window sizes

	// Globals for IMGUI menu
	inline int16_t menu_key = VK_INSERT;
	inline int16_t panic_key = VK_END;
	inline bool show_menu = false;

	// Globals needed internally (DONT CHANGE THOSE)
	inline int32_t height = GetSystemMetrics(1);
	inline int32_t width = GetSystemMetrics(0);
};
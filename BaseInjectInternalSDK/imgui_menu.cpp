#include "pch.h"
#include "imguisettings.h"
#include "imgui/imgui_internal.h"

void toggle_button(const char* str_id, bool* v)
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	const ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const float height = ImGui::GetFrameHeight();
	const float width = height * 1.55f;
	const float radius = height * 0.50f;

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked()) *v = !*v;
	const ImGuiContext& gg = *GImGui;
	constexpr float anim_speed = 0.085f;
	if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))
		float t_anim = ImSaturate(gg.LastActiveIdTimer / anim_speed);
	if (ImGui::IsItemHovered())
		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? ImVec4(0, 0.784, 0.317, 0.8) : ImVec4(1, 0.266, 0.266, 0.8)), height * 0.5f);
	else
		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? ImVec4(0,0.784,0.317,1) : ImVec4(1,0.266,0.266,1)), height * 0.50f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(34, 35, 43, 255));
}

void im_gui_menu::show()
{
	char buf[200];
	sprintf(buf, "CompanyName - ProductName             FPS: %0.f             Build Date: %s @ %s###MenuTitle", ImGui::GetIO().Framerate, __DATE__, __TIME__);

	ImGui::SetNextWindowSize(ImVec2(680, 600));
	ImGui::Begin(buf, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);
	ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

	ImGui::BeginTabBar("Settings#left_tabs_bar", ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_NoTooltip);

	if (ImGui::BeginTabItem("Options")) {
		if (ImGui::Button("Save Settings")) im_gui_settings::save_settings(); ImGui::SameLine(); if (ImGui::Button("Load Settings")) im_gui_settings::load_settings();
		
		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Debug")) {

		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void im_gui_menu::operations()
{
	if (Globals::show_menu) show();


	// Hacks - Locks
}

std::string im_gui_menu::draw_helper::string_to_utf8(const std::string& str)
{
	static const int nw_len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);

	auto* pw_buf = new wchar_t[nw_len + 1];
	ZeroMemory(pw_buf, nw_len * 2 + 2);

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pw_buf, nw_len);

	const int n_len = ::WideCharToMultiByte(CP_UTF8, 0, pw_buf, -1, nullptr, NULL, nullptr, nullptr);

	auto p_buf = new char[n_len + 1];
	ZeroMemory(p_buf, n_len + 1);

	WideCharToMultiByte(CP_UTF8, 0, pw_buf, nw_len, p_buf, n_len, nullptr, nullptr);

	std::string ret_str(p_buf);

	delete[]pw_buf;
	delete[]p_buf;

	pw_buf = nullptr;
	p_buf = nullptr;

	return ret_str;
}

void im_gui_menu::draw_helper::draw_stroke_text(const int x, const int y, const ImVec4 color, const char* str)
{
	ImFont a;
	const auto utf_8_1 = std::string(str);
	const std::string utf_8_2 = string_to_utf8(utf_8_1);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), utf_8_2.c_str());
}

void im_gui_menu::draw_helper::draw_new_text(const int x, const int y, const ImVec4 color, const char* str)
{
	ImFont a;
	const auto utf_8_1 = std::string(str);
	const std::string utf_8_2 = string_to_utf8(utf_8_1);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), utf_8_2.c_str());
}

void im_gui_menu::draw_helper::draw_rect(const int x, const int y, const int w, const int h, const ImVec4 color, const int thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0, thickness);
}

void im_gui_menu::draw_helper::draw_filled_rect(const int x, const int y, const int w, const int h, const ImVec4 color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 20.0, ~0);
}

void im_gui_menu::draw_helper::draw_circle_filled(const int x, const int y, const int radius, const ImVec4 color)
{
	ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color));
}

void im_gui_menu::draw_helper::draw_circle(const int x, const int y, const int radius, const ImVec4 color, const int segments)
{
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(color), segments);
}

void im_gui_menu::draw_helper::draw_triangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const ImVec4 color, const float thickne)
{
	ImGui::GetForegroundDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(color), thickne);
}

void im_gui_menu::draw_helper::draw_triangle_filled(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const ImVec4 color)
{
	ImGui::GetForegroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), ImGui::ColorConvertFloat4ToU32(color));
}

void im_gui_menu::draw_helper::draw_line(const int x1, const int y1, const int x2, const int y2, const ImVec4 color, const int thickness)
{
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(color), thickness);
}

void im_gui_menu::draw_helper::draw_corner_box(const int x, const int y, const int w, const int h, const int border_px, const ImVec4 color)
{
	draw_filled_rect(x + border_px, y, w / 3, border_px, color); //top 
	draw_filled_rect(x + w - w / 3 + border_px, y, w / 3, border_px, color); //top 
	draw_filled_rect(x, y, border_px, h / 3, color); //left 
	draw_filled_rect(x, y + h - h / 3 + border_px * 2, border_px, h / 3, color); //left 
	draw_filled_rect(x + border_px, y + h + border_px, w / 3, border_px, color); //bottom 
	draw_filled_rect(x + w - w / 3 + border_px, y + h + border_px, w / 3, border_px, color); //bottom 
	draw_filled_rect(x + w + border_px, y, border_px, h / 3, color);//right 
	draw_filled_rect(x + w + border_px, y + h - h / 3 + border_px * 2, border_px, h / 3, color);//right 
}

void im_gui_menu::draw_helper::text_to_screen(const ImVec2 pos, const ImColor color, const char* text_begin, const char* text_end, const float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), pos, color, text_begin, text_end, wrap_width, cpu_fine_clip_rect);
}

void im_gui_menu::draw_helper::rect_filled(const int x0, const int y0, const int x1, const int y1, const ImColor color, const float rounding, const int rounding_corners_flags)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}

void im_gui_menu::draw_helper::line(const ImVec2 a, const ImVec2 b, const ImColor color, const float thickness)
{
	ImGui::GetForegroundDrawList()->AddLine(a, b, color, thickness);
}

void im_gui_menu::draw_helper::easy_text(const ImVec2 pos, const ImColor color, const char* text, const int width_text)
{
	text_to_screen(pos, color, text, text + strlen(text), width_text, 0);
}

void im_gui_menu::draw_helper::easy_text_large(const ImVec2 pos, const ImColor color, const char* text)
{
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize() + 20, pos, color, text, text + strlen(text),
		800, nullptr);
}

void im_gui_menu::draw_helper::draw_box(const ImColor color, const int x, const int y, const int w, const int h)
{
	constexpr float thicc = 2.0f;

	// ------
	// |    |
	line(ImVec2(x, y), ImVec2(x + w, y), color, thicc);

	// |
	// |
	// |
	line(ImVec2(x, y), ImVec2(x, y + h), color, thicc);

	//      |
	//      |
	//      |
	line(ImVec2(x + w, y), ImVec2(x + w, y + h), color, thicc);

	// |    |
	// ------
	line(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thicc);
}

void im_gui_menu::draw_helper::circle(const ImVec2 point, const ImColor color, const float radius, const int num_segments, const float thickness)
{
	ImGui::GetForegroundDrawList()->AddCircle(point, radius, color, num_segments, thickness);
}

void im_gui_menu::draw_helper::progress(const int x, const int y, const int w, const int h, int phealth)
{
	if (phealth > 100) phealth = 100;
	const int health_value = max(0, min(phealth, 100));
	const float health_perc = health_value / 100.f;


	const ImVec4 color1(0.0f, 1.0f, 0.0f, 1.0f);
	const ImVec4 color2(1.0f, 1.0f, 0.0f, 1.0f);
	const ImVec4 color3(1.0f, 0.0f, 0.0f, 1.0f);
	const float factor_color1 = max(health_perc - 0.5f, 0.0f);
	const float factor_color2 = 0.5f - fabs(0.5f - health_perc);
	const float factor_color3 = max(0.5f - health_perc, 0.0f);

	ImVec4 bar_color;

	bar_color.x = (color1.x * factor_color1 + color2.x * factor_color2 + color3.x * factor_color3) * 2.0f;
	bar_color.y = (color1.y * factor_color1 + color2.y * factor_color2 + color3.y * factor_color3) * 2.0f;
	bar_color.z = (color1.z * factor_color1 + color2.z * factor_color2 + color3.z * factor_color3) * 2.0f;
	bar_color.w = 1.0f;

	rect_filled(x, y, x + w, y + static_cast<int>((static_cast<float>(h) / 100.0f) * static_cast<float>(phealth)), bar_color, 20.0f, ~0);
}

void im_gui_menu::draw_helper::progress_background(const int x, const int y, const int w, const int h)
{
	const auto bar_color = ImVec4(0.13f, 0.13f, 0.13f, 0.63f);

	rect_filled(x, y, x + w, y + static_cast<int>((static_cast<float>(h) / 100.0f) * 100), bar_color, 20.0f, ~0);
}

void im_gui_menu::draw_helper::box(const ImVec2 v_pos, const ImVec2 v_size, const float f_thickness, const ImVec4 v_color)
{
	ImGui::GetForegroundDrawList()->AddRect(v_pos, ImVec2(v_pos.x + v_size.x, v_pos.y + v_size.y), ImGui::ColorConvertFloat4ToU32(v_color), 0, 0, f_thickness);
}
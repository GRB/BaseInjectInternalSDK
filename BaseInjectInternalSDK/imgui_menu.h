#pragma once

namespace im_gui_menu {
	void show();
	void operations();

	class draw_helper {
	public:
		static std::string string_to_utf8(const std::string& str);
		static void draw_stroke_text(int x, int y, ImVec4 color, const char* str);
		static void draw_new_text(int x, int y, ImVec4 color, const char* str);
		static void draw_rect(int x, int y, int w, int h, ImVec4 color, int thickness);
		static void draw_filled_rect(int x, int y, int w, int h, ImVec4 color);
		static void draw_circle_filled(int x, int y, int radius, ImVec4 color);
		static void draw_circle(int x, int y, int radius, ImVec4 color, int segments);
		static void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, ImVec4 color, float thickne);
		static void draw_triangle_filled(int x1, int y1, int x2, int y2, int x3, int y3, ImVec4 color);
		static void draw_line(int x1, int y1, int x2, int y2, ImVec4 color, int thickness);
		static void draw_corner_box(int x, int y, int w, int h, int border_px, ImVec4 color);
		static void text_to_screen(ImVec2 pos, ImColor color, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect);
		static void rect_filled(int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags);
		static void line(ImVec2 a, ImVec2 b, ImColor color, float thickness);
		static void easy_text(ImVec2 pos, ImColor color, const char* text, int width_text);
		static void easy_text_large(ImVec2 pos, ImColor color, const char* text);
		static void draw_box(ImColor color, int x, int y, int w, int h);
		static void circle(ImVec2 point, ImColor color, float radius, int num_segments, float thickness);
		static void progress(int x, int y, int w, int h, int phealth);
		static void progress_background(int x, int y, int w, int h);
		static void box(ImVec2 v_pos, ImVec2 v_size, float f_thickness, ImVec4 v_color);
	};
}
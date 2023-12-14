#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "framework.h"
#include "config.h"


extern float color_accent_menu[4];
extern float color_background_menu[4];
extern float color_text_menu[4];
inline ImFont* serif_font;
inline ImFont* ico;
inline ImFont* ico_two;
inline ImFont* inter_min;
inline ImFont* remodz_image;
inline ImFont* remodz_icon;
inline ImFont* tab_label;

inline const char* keys[] = {
    "None",
    "Mouse 1",
    "Mouse 2",
    "CN",
    "Mouse 3",
    "Mouse 4",
    "Mouse 5",
    "-",
    "Back",
    "Tab",
    "-",
    "-",
    "CLR",
    "Enter",
    "-",
    "-",
    "Shift",
    "CTL",
    "Menu",
    "Pause",
    "Caps Lock",
    "KAN",
    "-",
    "JUN",
    "FIN",
    "KAN",
    "-",
    "Escape",
    "CON",
    "NCO",
    "ACC",
    "MAD",
    "Space",
    "PGU",
    "PGD",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "SEL",
    "PRI",
    "EXE",
    "PRI",
    "INSERT",
    "Delete",
    "HEL",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "WIN",
    "WIN",
    "APP",
    "-",
    "SLE",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "MUL",
    "ADD",
    "SEP",
    "MIN",
    "Delete",
    "DIV",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "NUM",
    "SCR",
    "EQU",
    "MAS",
    "TOY",
    "OYA",
    "OYA",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "-",
    "Shift",
    "Shift",
    "Ctrl",
    "Ctrl",
    "Alt",
    "Alt"
};

inline bool new_value(config::item_t* var)
{
    bool value_changed = false;
    int key = var->get<int>();

    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;

    for (auto i = 0; i < 5; i++) {
        if (io.MouseDown[i]) {
            switch (i) {
            case 0:
                key = VK_LBUTTON;
                break;
            case 1:
                key = VK_RBUTTON;
                break;
            case 2:
                key = VK_MBUTTON;
                break;
            case 3:
                key = VK_XBUTTON1;
                break;
            case 4:
                key = VK_XBUTTON2;
                break;
            }
            value_changed = true;
            ImGui::ClearActiveID();
        }
    }
    if (!value_changed) {
        for (auto i = VK_BACK; i <= VK_RMENU; i++) {
            if (io.KeysDown[i]) {
                key = i;
                value_changed = true;
                ImGui::ClearActiveID();
            }
        }
    }

    if (io.KeysDown[VK_ESCAPE]) {
        var->get<int>() = 0;
        ImGui::ClearActiveID();
    }
    else {
        var->get<int>() = key;
    }

    return value_changed;
}

namespace color {

    inline ImVec4 background = ImColor(20, 19, 19, 150);
    inline ImVec4 background_tab = ImColor(21, 23, 23, 150);

    inline ImVec4 tab_active = ImColor(45, 45, 52, 225);
    inline ImVec4 tab_hovered = ImColor(45, 45, 52, 105);
    inline ImVec4 tab_default = ImColor(45, 45, 52, 0);

    inline ImVec4 tab_line_active = ImColor(66, 220, 238, 150);
    inline ImVec4 tab_line_hovered = ImColor(66, 220, 238, 80);
    inline ImVec4 tab_line_default = ImColor(80, 90, 105, 0);

    inline ImVec4 text = ImColor(255, 255, 255, 255);
    inline ImVec4 text_active = ImColor(255, 255, 255, 255);
    inline ImVec4 text_hovered = ImColor(170, 180, 190, 255);
    inline ImVec4 text_default = ImColor(170, 180, 190, 255);

    inline ImVec4 background_scrollbar = ImColor(21, 23, 23, 150);

    inline ImVec4 scroll_active = ImColor(66, 220, 238, 200);
    inline ImVec4 scroll_hovered = ImColor(66, 220, 238, 170);
    inline ImVec4 scroll_default = ImColor(66, 220, 238, 150);

    inline ImVec4 checkbox_active = ImColor(26, 26, 26, 180);
    inline ImVec4 checkbox_hovered = ImColor(39, 41, 44, 150);
    inline ImVec4 checkbox_default = ImColor(39, 41, 44, 130);

    inline ImVec4 checkMark_color = ImColor(17, 225, 252, 255);
    inline ImVec4 checkbox_background = ImColor(90, 105, 120, 80);

    inline ImVec4 slider_active = ImColor(72, 80, 86, 255);
    inline ImVec4 slider_hovered = ImColor(72, 80, 86, 225);
    inline ImVec4 slider_default = ImColor(72, 80, 86, 225);

    inline ImVec4 car_slider_Active = ImColor(41, 44, 48, 160);
    inline ImVec4 car_slider_Hovered = ImColor(41, 44, 48, 150);
    inline ImVec4 car_slider_default = ImColor(41, 44, 48, 140);

    inline ImVec4 circle_sliderActive = ImColor(51, 54, 58, 255);
    inline ImVec4 circle_sliderHovered = ImColor(51, 54, 58, 255);
    inline ImVec4 circle_slider_default = ImColor(51, 54, 58, 255);

    inline ImVec4 combo_active = ImColor(49, 51, 54, 0);
    inline ImVec4 combo_hovered = ImColor(49, 51, 54, 0);
    inline ImVec4 combo_default = ImColor(39, 41, 44, 0);

    inline ImVec4 selectable_active = ImColor(70, 70, 77, 180);
    inline ImVec4 selectable_hovered = ImColor(49, 51, 54, 170);
    inline ImVec4 selectable_default = ImColor(70, 70, 77, 0);

    inline ImVec4 input_active = ImColor(21, 21, 26, 160);
    inline ImVec4 input_hovered = ImColor(15, 15, 17, 160);
    inline ImVec4 input_default = ImColor(11, 11, 16, 160);

    inline ImVec4 background_picker = ImColor(20, 25, 30, 255);
    inline ImVec4 background_color = ImColor(20, 25, 30, 255);
}

namespace UI {

    bool CheckBox(const char* label, config::item_t* var);
    bool Tab(const char* ico0, const char* label, bool selected, const ImVec2& size_arg);
    bool BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags);
    bool BeginComboPopup(ImGuiID popup_id, const ImRect& bb, ImGuiComboFlags flags);
    void EndCombo();
    bool BeginComboPreview();
    void EndComboPreview();
    bool Combo(const char* label, config::item_t* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items);
    IMGUI_API bool Combo(const char* label, config::item_t* current_item, const char* const items[], int items_count, int height_in_items);
    IMGUI_API bool Combo(const char* label, config::item_t* current_item, const char* items_separated_by_zeros, int height_in_items);
    bool SliderBehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* p_v, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags, ImRect* out_grab_bb);
    bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
    IMGUI_API bool SliderInt(const char* label, config::item_t* var, int v_min, int v_max, const char* format, ImGuiSliderFlags flags);
    IMGUI_API bool          SliderFloat(const char* label, config::item_t* var, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool          SliderInt(const char* label, config::item_t* var, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
    bool KeyBind(const char* label, int* key, int* mode);
}



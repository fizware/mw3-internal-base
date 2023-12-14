#include "menu.h"


bool theme = true;
int tabs = 0;
int active_tab = 0;
float tab_alpha = 0.f;
float tab_add;

void render_SliderFloat(const char* id, float& value, float lineLength, float minValue, float maxValue, ImU32 leftColor, const char* format)
{

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    ImVec2 linePos = window->DC.CursorPos;
    ImVec2 lineSize(lineLength, 4.0f);

    float circleRadius = 8.0f;
    float lineStartX = linePos.x;
    float lineEndX = linePos.x + lineSize.x;
    float clampedValue = std::clamp(value, minValue, maxValue);
    float circlePosX = lineStartX + (lineEndX - lineStartX) * ((clampedValue - minValue) / (maxValue - minValue));
    ImVec2 circlePos(circlePosX, linePos.y + lineSize.y / 2.0f);

    ImVec2 lineStartPos = linePos;
    ImVec2 lineEndPos = ImVec2(linePos.x + lineSize.x, linePos.y + lineSize.y);

    ImVec2 filledStartPos = lineStartPos;
    ImVec2 filledEndPos = ImVec2(circlePos.x, lineEndPos.y);
    window->DrawList->AddRectFilled(filledStartPos, filledEndPos, leftColor);

    ImVec2 lineStartPosRight = ImVec2(circlePos.x, lineStartPos.y);
    ImVec2 lineEndPosRight = lineEndPos;
    window->DrawList->AddRectFilled(lineStartPosRight, lineEndPosRight, IM_COL32(128, 128, 128, 255));

    ImGui::SetCursorScreenPos(ImVec2(circlePos.x - circleRadius, circlePos.y - circleRadius));
    ImGui::PushID(id);
    ImGui::InvisibleButton("##circle", ImVec2(circleRadius * 2.0f, circleRadius * 2.0f));
    ImGui::PopID();

    static bool activeSlider = false;

    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
    {
        if (!activeSlider)
        {
            activeSlider = true;
            value = clampedValue;
        }

        ImVec2 mouseDelta = ImGui::GetIO().MouseDelta;
        float deltaValue = (mouseDelta.x / (lineEndX - lineStartX)) * (maxValue - minValue);
        value += deltaValue;
        value = std::clamp(value, minValue, maxValue);
    }
    else if (!ImGui::IsMouseDown(0))
    {
        activeSlider = false;
    }

    window->DrawList->AddCircleFilled(circlePos, circleRadius, IM_COL32(255, 255, 255, 255));

    ImGui::SetCursorScreenPos(ImVec2(linePos.x + lineSize.x / 2.0f + 10.f, linePos.y - ImGui::GetTextLineHeight() / 2.0f - 15.f));
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), format, value);
    ImGui::PopFont();
}


void TransP(const char* text) {
    ImVec4 clear_color = ImVec4(1.00f, 1.00f, 1.00f, 0.00); // Transparent background
    ImGui::GetBackgroundDrawList()->AddRectFilled(
        ImGui::GetItemRectMin(),
        ImGui::GetItemRectMax(),
        ImGui::ColorConvertFloat4ToU32(clear_color)
    );
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), text);
}

#define WIDTH 500 //WIDTH of menu
#define HEIGHT 500 //HEIGHT of menu
void cMenu::Menu()
{
    ImGui::Begin(XOR("##MENU"), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse);
    {
        ImGui::Text("Test");
    }

    ImGui::End();
}
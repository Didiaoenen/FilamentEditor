/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Internal/Converter.h"

#include "FEditorUI/Widgets/Buttons/ButtonSmall.h"

FEditorUI::Widgets::Buttons::ButtonSmall::ButtonSmall(const std::string& p_label) :
	label(p_label)
{
	auto& style = ImGui::GetStyle();

	idleBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_Button]);
	hoveredBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonHovered]);
	clickedBackgroundColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_ButtonActive]);
	textColor = Internal::Converter::ToColor(style.Colors[ImGuiCol_Text]);
}

void FEditorUI::Widgets::Buttons::ButtonSmall::_Draw_Impl()
{
	auto& style = ImGui::GetStyle();

	auto defaultIdleColor		= style.Colors[ImGuiCol_Button];
	auto defaultHoveredColor	= style.Colors[ImGuiCol_ButtonHovered];
	auto defaultClickedColor	= style.Colors[ImGuiCol_ButtonActive];
	auto defaultTextColor		= style.Colors[ImGuiCol_Text];

	style.Colors[ImGuiCol_Button]			= FEditorUI::Internal::Converter::ToImVec4(idleBackgroundColor);
	style.Colors[ImGuiCol_ButtonHovered]	= FEditorUI::Internal::Converter::ToImVec4(hoveredBackgroundColor);
	style.Colors[ImGuiCol_ButtonActive]		= FEditorUI::Internal::Converter::ToImVec4(clickedBackgroundColor);
	style.Colors[ImGuiCol_Text]				= FEditorUI::Internal::Converter::ToImVec4(textColor);

	if (ImGui::SmallButton((label + m_widgetID).c_str()))
		ClickedEvent.Invoke();

	style.Colors[ImGuiCol_Button]			= defaultIdleColor;
	style.Colors[ImGuiCol_ButtonHovered]	= defaultHoveredColor;
	style.Colors[ImGuiCol_ButtonActive]		= defaultClickedColor;
	style.Colors[ImGuiCol_Text]				= defaultTextColor;
}

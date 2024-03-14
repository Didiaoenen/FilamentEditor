/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Buttons/ButtonArrow.h"

FEditorUI::Widgets::Buttons::ButtonArrow::ButtonArrow(ImGuiDir p_direction) :
	direction(p_direction)
{
}

void FEditorUI::Widgets::Buttons::ButtonArrow::_Draw_Impl()
{
	if (ImGui::ArrowButton(m_widgetID.c_str(), direction))
		ClickedEvent.Invoke();
}

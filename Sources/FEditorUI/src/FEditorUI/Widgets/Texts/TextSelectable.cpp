/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/TextSelectable.h"

FEditorUI::Widgets::Texts::TextSelectable::TextSelectable(const std::string & p_content, bool p_selected, bool p_disabled) :
	Text(p_content), selected(p_selected), disabled(p_disabled)
{
}

void FEditorUI::Widgets::Texts::TextSelectable::_Draw_Impl()
{
	if (ImGui::Selectable((content + m_widgetID).c_str(), &selected, disabled ? ImGuiSelectableFlags_Disabled : ImGuiSelectableFlags_None))
	{
		ClickedEvent.Invoke(selected);

		if (selected)
			SelectedEvent.Invoke();
		else
			UnselectedEvent.Invoke();
	}
}

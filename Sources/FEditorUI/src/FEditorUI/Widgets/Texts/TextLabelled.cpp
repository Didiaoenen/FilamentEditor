/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/TextLabelled.h"

FEditorUI::Widgets::Texts::TextLabelled::TextLabelled(const std::string& p_content, const std::string& p_label) :
	Text(p_content), label(p_label)
{
}

void FEditorUI::Widgets::Texts::TextLabelled::_Draw_Impl()
{
	ImGui::LabelText((label + m_widgetID).c_str(), content.c_str());
}

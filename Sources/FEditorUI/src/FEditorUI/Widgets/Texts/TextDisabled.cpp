/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/TextDisabled.h"

FEditorUI::Widgets::Texts::TextDisabled::TextDisabled(const std::string & p_content) :
	Text(p_content)
{
}

void FEditorUI::Widgets::Texts::TextDisabled::_Draw_Impl()
{
	ImGui::TextDisabled(content.c_str());
}

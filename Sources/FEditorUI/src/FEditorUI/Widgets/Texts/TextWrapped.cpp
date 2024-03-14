/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/TextWrapped.h"

FEditorUI::Widgets::Texts::TextWrapped::TextWrapped(const std::string & p_content) :
	Text(p_content)
{
}

void FEditorUI::Widgets::Texts::TextWrapped::_Draw_Impl()
{
	ImGui::TextWrapped(content.c_str());
}

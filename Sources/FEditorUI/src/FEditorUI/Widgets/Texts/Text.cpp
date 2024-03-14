/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/Text.h"

FEditorUI::Widgets::Texts::Text::Text(const std::string & p_content) :
	DataWidget(content),
	content(p_content)
{
}

void FEditorUI::Widgets::Texts::Text::_Draw_Impl()
{
	ImGui::Text(content.c_str());
}

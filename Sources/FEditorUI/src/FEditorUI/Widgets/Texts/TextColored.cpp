/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Texts/TextColored.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Widgets::Texts::TextColored::TextColored(const std::string& p_content, const Types::Color& p_color) :
	Text(p_content), color(p_color)
{
}

void FEditorUI::Widgets::Texts::TextColored::_Draw_Impl()
{
	ImGui::TextColored(Internal::Converter::ToImVec4(color), content.c_str());
}

/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Visual/Image.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Widgets::Visual::Image::Image(uint32_t p_textureID, const OvMaths::FVector2& p_size) :
	textureID{ p_textureID }, size(p_size)
{
	
}

void FEditorUI::Widgets::Visual::Image::_Draw_Impl()
{
	ImGui::Image(textureID.raw, Internal::Converter::ToImVec2(size), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
}

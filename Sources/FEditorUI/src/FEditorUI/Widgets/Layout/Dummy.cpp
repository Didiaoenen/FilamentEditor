/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Layout/Dummy.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Widgets::Layout::Dummy::Dummy(const OvMaths::FVector2& p_size) : size(p_size)
{
}

void FEditorUI::Widgets::Layout::Dummy::_Draw_Impl()
{
	ImGui::Dummy(Internal::Converter::ToImVec2(size));
}

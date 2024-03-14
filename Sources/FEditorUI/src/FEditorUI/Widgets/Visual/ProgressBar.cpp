/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Visual/ProgressBar.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Widgets::Visual::ProgressBar::ProgressBar(float p_fraction, const OvMaths::FVector2 & p_size, const std::string & p_overlay) :
	fraction(p_fraction), size(p_size), overlay(p_overlay)
{
}

void FEditorUI::Widgets::Visual::ProgressBar::_Draw_Impl()
{
	ImGui::ProgressBar(fraction, Internal::Converter::ToImVec2(size), !overlay.empty() ? overlay.c_str() : nullptr);
}

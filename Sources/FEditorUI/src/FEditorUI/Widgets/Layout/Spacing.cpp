/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Layout/Spacing.h"

FEditorUI::Widgets::Layout::Spacing::Spacing(uint16_t p_spaces) : spaces(p_spaces)
{
}

void FEditorUI::Widgets::Layout::Spacing::_Draw_Impl()
{
	for (uint16_t i = 0; i < spaces; ++i)
	{
		ImGui::Spacing();

		if (i + 1 < spaces)
			ImGui::SameLine();
	}
}

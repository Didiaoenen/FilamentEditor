/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Plugins/ContextualMenu.h"

void FEditorUI::Plugins::ContextualMenu::Execute()
{
	if (ImGui::BeginPopupContextItem())
	{
		DrawWidgets();
		ImGui::EndPopup();
	}
}

void FEditorUI::Plugins::ContextualMenu::Close()
{
	ImGui::CloseCurrentPopup();
}

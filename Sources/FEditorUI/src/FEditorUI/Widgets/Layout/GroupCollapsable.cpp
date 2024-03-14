/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Layout/GroupCollapsable.h"
#include "FEditorUI/ImGui/imgui_internal.h"

FEditorUI::Widgets::Layout::GroupCollapsable::GroupCollapsable(const std::string & p_name) :
	name(p_name)
{
}

void FEditorUI::Widgets::Layout::GroupCollapsable::_Draw_Impl()
{
	bool previouslyOpened = opened;

	if (ImGui::CollapsingHeader(name.c_str(), closable ? &opened : nullptr))
		Group::_Draw_Impl();

	if (opened != previouslyOpened)
	{
		if (opened)
			OpenEvent.Invoke();
		else
			CloseEvent.Invoke();
	}
}

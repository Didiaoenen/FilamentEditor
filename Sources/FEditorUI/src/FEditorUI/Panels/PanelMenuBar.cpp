/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Panels/PanelMenuBar.h"

void FEditorUI::Panels::PanelMenuBar::_Draw_Impl()
{
	if (!m_widgets.empty() && ImGui::BeginMainMenuBar())
	{
		DrawWidgets();
		ImGui::EndMainMenuBar();
	}
}
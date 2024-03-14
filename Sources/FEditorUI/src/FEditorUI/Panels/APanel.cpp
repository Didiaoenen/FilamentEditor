/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <algorithm>

#include "FEditorUI/Panels/APanel.h"

uint64_t FEditorUI::Panels::APanel::__PANEL_ID_INCREMENT = 0;

FEditorUI::Panels::APanel::APanel()
{
	m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
}

void FEditorUI::Panels::APanel::Draw()
{
	if (enabled)
		_Draw_Impl();
}

const std::string & FEditorUI::Panels::APanel::GetPanelID() const
{
	return m_panelID;
}

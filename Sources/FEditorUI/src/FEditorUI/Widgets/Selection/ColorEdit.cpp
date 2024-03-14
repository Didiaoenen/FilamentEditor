/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Selection/ColorEdit.h"

FEditorUI::Widgets::Selection::ColorEdit::ColorEdit(bool p_enableAlpha, const Types::Color & p_defaultColor) :
	DataWidget<Types::Color>(color), enableAlpha(p_enableAlpha), color(p_defaultColor)
{
}

void FEditorUI::Widgets::Selection::ColorEdit::_Draw_Impl()
{
	int flags = !enableAlpha ? ImGuiColorEditFlags_NoAlpha : 0;
	bool valueChanged = false;

	if (enableAlpha)
		valueChanged = ImGui::ColorEdit4(m_widgetID.c_str(), &color.r, flags);
	else
		valueChanged =ImGui::ColorEdit3(m_widgetID.c_str(), &color.r, flags);

	if (valueChanged)
	{
		ColorChangedEvent.Invoke(color);
		this->NotifyChange();
	}
}

/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/AWidget.h"

uint64_t FEditorUI::Widgets::AWidget::__WIDGET_ID_INCREMENT = 0;

FEditorUI::Widgets::AWidget::AWidget()
{
	m_widgetID = "##" + std::to_string(__WIDGET_ID_INCREMENT++);
}

void FEditorUI::Widgets::AWidget::LinkTo(const AWidget& p_widget)
{
	m_widgetID = p_widget.m_widgetID;
}

void FEditorUI::Widgets::AWidget::Destroy()
{
	m_destroyed = true;
}

bool FEditorUI::Widgets::AWidget::IsDestroyed() const
{
	return m_destroyed;
}

void FEditorUI::Widgets::AWidget::SetParent(Internal::WidgetContainer * p_parent)
{
	m_parent = p_parent;
}

bool FEditorUI::Widgets::AWidget::HasParent() const
{
	return m_parent;
}

FEditorUI::Internal::WidgetContainer * FEditorUI::Widgets::AWidget::GetParent()
{
	return m_parent;
}

void FEditorUI::Widgets::AWidget::Draw()
{
	if (enabled)
	{
		_Draw_Impl();

		if (m_autoExecutePlugins)
			ExecutePlugins();

		if (!lineBreak)
			ImGui::SameLine();
	}
}

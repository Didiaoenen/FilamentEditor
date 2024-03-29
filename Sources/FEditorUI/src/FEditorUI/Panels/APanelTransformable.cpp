/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Panels/APanelTransformable.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Panels::APanelTransformable::APanelTransformable
(
	const OvMaths::FVector2& p_defaultPosition,
	const OvMaths::FVector2& p_defaultSize,
	Settings::EHorizontalAlignment p_defaultHorizontalAlignment,
	Settings::EVerticalAlignment p_defaultVerticalAlignment,
	bool p_ignoreConfigFile
) :
	m_defaultPosition(p_defaultPosition),
	m_defaultSize(p_defaultSize),
	m_defaultHorizontalAlignment(p_defaultHorizontalAlignment),
	m_defaultVerticalAlignment(p_defaultVerticalAlignment),
	m_ignoreConfigFile(p_ignoreConfigFile)
{
}

void FEditorUI::Panels::APanelTransformable::SetPosition(const OvMaths::FVector2& p_position)
{
	m_position = p_position;
	m_positionChanged = true;
}

void FEditorUI::Panels::APanelTransformable::SetSize(const OvMaths::FVector2& p_size)
{
	m_size = p_size;
	m_sizeChanged = true;
}

void FEditorUI::Panels::APanelTransformable::SetAlignment(Settings::EHorizontalAlignment p_horizontalAlignment, Settings::EVerticalAlignment p_verticalAligment)
{
	m_horizontalAlignment = p_horizontalAlignment;
	m_verticalAlignment = p_verticalAligment;
	m_alignmentChanged = true;
}

const OvMaths::FVector2 & FEditorUI::Panels::APanelTransformable::GetPosition() const
{
	return m_position;
}

const OvMaths::FVector2 & FEditorUI::Panels::APanelTransformable::GetSize() const
{
	return m_size;
}

FEditorUI::Settings::EHorizontalAlignment FEditorUI::Panels::APanelTransformable::GetHorizontalAlignment() const
{
	return m_horizontalAlignment;
}

FEditorUI::Settings::EVerticalAlignment FEditorUI::Panels::APanelTransformable::GetVerticalAlignment() const
{
	return m_verticalAlignment;
}

void FEditorUI::Panels::APanelTransformable::UpdatePosition()
{
	if (m_defaultPosition.x != -1.f && m_defaultPosition.y != 1.f)
	{
		OvMaths::FVector2 offsettedDefaultPos = m_defaultPosition + CalculatePositionAlignmentOffset(true);
		ImGui::SetWindowPos(Internal::Converter::ToImVec2(offsettedDefaultPos), m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
	}

	if (m_positionChanged || m_alignmentChanged)
	{
		OvMaths::FVector2 offset = CalculatePositionAlignmentOffset(false);
		OvMaths::FVector2 offsettedPos(m_position.x + offset.x, m_position.y + offset.y);
		ImGui::SetWindowPos(Internal::Converter::ToImVec2(offsettedPos), ImGuiCond_Always);
		m_positionChanged = false;
		m_alignmentChanged = false;
	}
}

void FEditorUI::Panels::APanelTransformable::UpdateSize()
{
	/*
	if (m_defaultSize.x != -1.f && m_defaultSize.y != 1.f)
		ImGui::SetWindowSize(Internal::Converter::ToImVec2(m_defaultSize), m_ignoreConfigFile ? ImGuiCond_Once : ImGuiCond_FirstUseEver);
	*/
	if (m_sizeChanged)
	{
		ImGui::SetWindowSize(Internal::Converter::ToImVec2(m_size), ImGuiCond_Always);
		m_sizeChanged = false;
	}
}

void FEditorUI::Panels::APanelTransformable::CopyImGuiPosition()
{
	m_position = Internal::Converter::ToFVector2(ImGui::GetWindowPos());
}

void FEditorUI::Panels::APanelTransformable::CopyImGuiSize()
{
	m_size = Internal::Converter::ToFVector2(ImGui::GetWindowSize());
}

void FEditorUI::Panels::APanelTransformable::Update()
{
	if (!m_firstFrame)
	{
		if (!autoSize)
			UpdateSize();
		CopyImGuiSize();

		UpdatePosition();
		CopyImGuiPosition();
	}

	m_firstFrame = false;
}

OvMaths::FVector2 FEditorUI::Panels::APanelTransformable::CalculatePositionAlignmentOffset(bool p_default)
{
	OvMaths::FVector2 result(0.0f, 0.0f);

	switch (p_default ? m_defaultHorizontalAlignment : m_horizontalAlignment)
	{
	case FEditorUI::Settings::EHorizontalAlignment::CENTER:
		result.x -= m_size.x / 2.0f;
		break;
	case FEditorUI::Settings::EHorizontalAlignment::RIGHT:
		result.x -= m_size.x;
		break;
	}

	switch (p_default ? m_defaultVerticalAlignment : m_verticalAlignment)
	{
	case FEditorUI::Settings::EVerticalAlignment::MIDDLE:
		result.y -= m_size.y / 2.0f;
		break;
	case FEditorUI::Settings::EVerticalAlignment::BOTTOM:
		result.y -= m_size.y;
		break;
	}

	return result;
}

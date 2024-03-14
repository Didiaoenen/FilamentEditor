/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditor/Panels/AViewControllable.h"

FEditor::Panels::AViewControllable::AViewControllable
(
	const std::string& p_title,
	bool p_opened,
	const FEditorUI::Settings::PanelWindowSettings& p_windowSettings,
	bool p_enableFocusInputs
) : AView(p_title, p_opened, p_windowSettings), m_cameraController(*this, m_camera, m_cameraPosition, m_cameraRotation, p_enableFocusInputs)
{

}

void FEditor::Panels::AViewControllable::Update(float p_deltaTime)
{
	m_cameraController.HandleInputs(p_deltaTime);

	AView::Update(p_deltaTime);
}

FEditor::Core::CameraController& FEditor::Panels::AViewControllable::GetCameraController()
{
	return m_cameraController;
}

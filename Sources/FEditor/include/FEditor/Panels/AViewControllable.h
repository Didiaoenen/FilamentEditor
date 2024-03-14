/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditor/Panels/AView.h"
#include "FEditor/Core/CameraController.h"

namespace FEditor::Panels
{
	class AViewControllable : public FEditor::Panels::AView
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_enableFocusInputs
		*/
		AViewControllable
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings,
			bool p_enableFocusInputs = false
		);

		/**
		* Update the controllable view (Handle inputs)
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Returns the camera controller of the controllable view
		*/
		FEditor::Core::CameraController& GetCameraController();

	protected:
		FEditor::Core::CameraController m_cameraController;
	};
}
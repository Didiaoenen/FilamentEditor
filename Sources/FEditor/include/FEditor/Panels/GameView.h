/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvCore/SceneSystem/SceneManager.h>

#include "FEditor/Panels/AView.h"

namespace FEditor::Core { class EditorRenderer; }

namespace FEditor::Panels
{
	class GameView : public FEditor::Panels::AView
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		GameView
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the view
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Returns true if the game view has a camera
		*/
		bool HasCamera() const;

		/**
		* Returns the game view camera frustum or nothing if the game isn't playing
		*/
		std::optional<OvRendering::Data::Frustum> GetActiveFrustum() const;

	private:
		OvCore::SceneSystem::SceneManager& m_sceneManager;
		bool m_hasCamera = false;
	};
}
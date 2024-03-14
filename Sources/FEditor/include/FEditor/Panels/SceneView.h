/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditor/Panels/AViewControllable.h"
#include "FEditor/Core/GizmoBehaviour.h"

namespace FEditor::Panels
{
	class SceneView : public FEditor::Panels::AViewControllable
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		SceneView
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the scene view
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Render the actual scene
		* @param p_defaultRenderState
		*/
		void RenderScene(uint8_t p_defaultRenderState);

		/**
		* Render the scene for actor picking (Using unlit colors)
		*/
		void RenderSceneForActorPicking();

		/**
		* Render the scene for actor picking and handle the logic behind it
		*/
		void HandleActorPicking();

	private:
		OvCore::SceneSystem::SceneManager& m_sceneManager;
		OvRendering::Buffers::Framebuffer m_actorPickingFramebuffer;
		FEditor::Core::GizmoBehaviour m_gizmoOperations;
		FEditor::Core::EGizmoOperation m_currentOperation = FEditor::Core::EGizmoOperation::TRANSLATE;

		std::optional<std::reference_wrapper<OvCore::ECS::Actor>> m_highlightedActor;
		std::optional<FEditor::Core::GizmoBehaviour::EDirection> m_highlightedGizmoDirection;
	};
}
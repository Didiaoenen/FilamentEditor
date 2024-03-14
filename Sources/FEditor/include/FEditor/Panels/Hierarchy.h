/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvRendering/Resources/Loaders/TextureLoader.h>
#include <OvRendering/LowRenderer/Camera.h>

#include <OvCore/SceneSystem/SceneManager.h>

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Layout/Group.h>
#include <FEditorUI/Widgets/Layout/TreeNode.h>

namespace FEditor::Panels
{
	class Hierarchy : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Hierarchy
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);
		
		/**
		* Clear hierarchy nodes
		*/
		void Clear();

		/**
		* Unselect every widgets
		*/
		void UnselectActorsWidgets();

		/**
		* Select the widget corresponding to the given actor
		* @param p_actor
		*/
		void SelectActorByInstance(OvCore::ECS::Actor& p_actor);

		/**
		* Select the widget
		* @param p_actor
		*/
		void SelectActorByWidget(FEditorUI::Widgets::Layout::TreeNode& p_widget);

		/**
		* Attach the given actor linked widget to its parent widget
		* @param p_actor
		*/
		void AttachActorToParent(OvCore::ECS::Actor& p_actor);

		/**
		* Detach the given actor linked widget from its parent widget
		* @param p_actor
		*/
		void DetachFromParent(OvCore::ECS::Actor& p_actor);

		/**
		* Delete the widget referencing the given actor
		* @param p_actor
		*/
		void DeleteActorByInstance(OvCore::ECS::Actor& p_actor);

		/**
		* Add a widget referencing the given actor
		* @param p_actor
		*/
		void AddActorByInstance(OvCore::ECS::Actor& p_actor);

	public:
		FTools::Eventing::Event<OvCore::ECS::Actor&> ActorSelectedEvent;
		FTools::Eventing::Event<OvCore::ECS::Actor&> ActorUnselectedEvent;

	private:
		FEditorUI::Widgets::Layout::TreeNode* m_sceneRoot;

		std::unordered_map<OvCore::ECS::Actor*, FEditorUI::Widgets::Layout::TreeNode*> m_widgetActorLink;
	};
}
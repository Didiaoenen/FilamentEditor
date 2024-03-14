/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvRendering/Resources/Loaders/TextureLoader.h>

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Layout/GroupCollapsable.h>
#include <FEditorUI/Widgets/InputFields/InputText.h>
#include <FEditorUI/Widgets/Visual/Separator.h>
#include <FEditorUI/Widgets/Selection/CheckBox.h>
#include <FEditorUI/Widgets/Buttons/Button.h>
#include <FEditorUI/Widgets/Selection/ComboBox.h>

#include "FEditor/Panels/Hierarchy.h"
#include "FEditor/Panels/AssetBrowser.h"

namespace FEditor::Panels
{
	class Inspector : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Inspector
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Destructor
		*/
		~Inspector();

		/**
		* Focus the given actor
		* @param p_target
		*/
		void FocusActor(OvCore::ECS::Actor& p_target);

		/**
		* Unfocus the currently targeted actor
		*/
		void UnFocus();

		/**
		* Unfocus the currently targeted actor without removing listeners attached to this actor
		*/
		void SoftUnFocus();

		/**
		* Returns the currently selected actor
		*/
		OvCore::ECS::Actor* GetTargetActor() const;

		/**
		* Create the actor inspector for the given actor
		*/
		void CreateActorInspector(OvCore::ECS::Actor& p_target);

		/**
		* Draw the given component in inspector
		*/
		void DrawComponent(OvCore::ECS::Components::AComponent& p_component);

		/**
		* Draw the given behaviour in inspector
		*/
		void DrawBehaviour(OvCore::ECS::Components::Behaviour& p_behaviour);

		/**
		* Refresh the inspector
		*/
		void Refresh();

	private:
		OvCore::ECS::Actor* m_targetActor = nullptr;
		FEditorUI::Widgets::Layout::Group* m_actorInfo;
		FEditorUI::Widgets::Layout::Group* m_inspectorHeader;
		FEditorUI::Widgets::Selection::ComboBox* m_componentSelectorWidget;
        FEditorUI::Widgets::InputFields::InputText* m_scriptSelectorWidget;

		uint64_t m_componentAddedListener	= 0;
		uint64_t m_componentRemovedListener = 0;
		uint64_t m_behaviourAddedListener	= 0;
		uint64_t m_behaviourRemovedListener = 0;
		uint64_t m_destroyedListener		= 0;
	};
}
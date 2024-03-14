/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FEditorUI/Widgets/Texts/Text.h>
#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Layout/Group.h>
#include <FEditorUI/Widgets/Layout/Columns.h>
#include <OvRendering/Resources/Shader.h>

namespace OvCore::Resources { class Material; }

namespace FEditor::Panels
{
	class MaterialEditor : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		MaterialEditor
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Refresh the material editor
		*/
		void Refresh();

		/**
		* Defines the target material of the material editor
		* @param p_newTarget
		*/
		void SetTarget(OvCore::Resources::Material& p_newTarget);

		/**
		* Returns the target of the material editor
		*/
		OvCore::Resources::Material* GetTarget() const;

		/**
		* Remove the target of the material editor (Clear the material editor)
		*/
		void RemoveTarget();

		/**
		* Launch the preview of the currently targeted material
		*/
		void Preview();

		/**
		* Reset material
		*/
		void Reset();
		
	private:
		void OnMaterialDropped();
		void OnShaderDropped();

		void CreateHeaderButtons();
		void CreateMaterialSelector();
		void CreateShaderSelector();
		void CreateMaterialSettings();
		void CreateShaderSettings();

		void GenerateShaderSettingsContent();
		void GenerateMaterialSettingsContent();

	private:
		OvCore::Resources::Material* m_target		= nullptr;
		OvRendering::Resources::Shader* m_shader	= nullptr;

		FEditorUI::Widgets::Texts::Text* m_targetMaterialText	= nullptr;
		FEditorUI::Widgets::Texts::Text* m_shaderText			= nullptr;

		FTools::Eventing::Event<> m_materialDroppedEvent;
		FTools::Eventing::Event<> m_shaderDroppedEvent;

		FEditorUI::Widgets::Layout::Group* m_settings			= nullptr;
		FEditorUI::Widgets::Layout::Group* m_materialSettings	= nullptr;
		FEditorUI::Widgets::Layout::Group* m_shaderSettings		= nullptr;

		FEditorUI::Widgets::Layout::Columns<2>* m_shaderSettingsColumns = nullptr;
		FEditorUI::Widgets::Layout::Columns<2>* m_materialSettingsColumns = nullptr;
	};
}
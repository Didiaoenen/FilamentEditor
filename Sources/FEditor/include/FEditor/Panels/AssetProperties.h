/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <variant>

#include <FTools/Filesystem/IniFile.h>
#include <FTools/Eventing/Event.h>

#include <FEditorUI/Widgets/Texts/Text.h>
#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Layout/Group.h>
#include <FEditorUI/Widgets/Layout/Columns.h>

#include <OvRendering/Resources/Model.h>
#include <OvRendering/Resources/Texture.h>

namespace FEditor::Panels
{
	class AssetProperties : public FEditorUI::Panels::PanelWindow
	{
	public:
		using EditableAssets = std::variant<OvRendering::Resources::Model*, OvRendering::Resources::Texture*>;

		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AssetProperties
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Defines the target of the asset settings editor
		* @param p_path
		*/
		void SetTarget(const std::string& p_path);

        /**
        * Refresh the panel to show the current target settings
        */
        void Refresh();

		/**
		* Launch the preview of the target asset
		*/
		void Preview();

	private:
		void CreateHeaderButtons();
        void CreateAssetSelector();
		void CreateSettings();
		void CreateInfo();
		void CreateModelSettings();
		void CreateTextureSettings();
		void Apply();

	private:
		std::string m_resource;

        FTools::Eventing::Event<> m_targetChanged;
        FEditorUI::Widgets::Layout::Group* m_settings = nullptr;
        FEditorUI::Widgets::Layout::Group* m_info = nullptr;
        FEditorUI::Widgets::Buttons::Button* m_applyButton = nullptr;
        FEditorUI::Widgets::Buttons::Button* m_revertButton = nullptr;
        FEditorUI::Widgets::Buttons::Button* m_previewButton = nullptr;
        FEditorUI::Widgets::Buttons::Button* m_resetButton = nullptr;
        FEditorUI::Widgets::AWidget* m_headerSeparator = nullptr;
        FEditorUI::Widgets::AWidget* m_headerLineBreak = nullptr;
		FEditorUI::Widgets::Layout::Columns<2>* m_settingsColumns = nullptr;
		FEditorUI::Widgets::Layout::Columns<2>* m_infoColumns = nullptr;
        FEditorUI::Widgets::Texts::Text* m_assetSelector = nullptr;
		std::unique_ptr<FTools::Filesystem::IniFile> m_metadata;
	};
}
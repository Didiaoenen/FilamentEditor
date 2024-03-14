/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <filesystem>
#include <unordered_map>
#include <queue>

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Layout/TreeNode.h>
#include <OvRendering/Resources/Loaders/TextureLoader.h>

namespace FEditor::Panels
{
	/**
	* A panel that handle asset management
	*/
	class AssetBrowser : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @parma p_opened
		* @param p_windowSettings
		* @param p_engineAssetFolder
		* @param p_projectAssetFolder
		* @param p_projectScriptFolder
		*/
		AssetBrowser
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings,
			const std::string& p_engineAssetFolder = "",
			const std::string& p_projectAssetFolder = "",
			const std::string& p_projectScriptFolder = ""
		);

		/**
		* Fill the asset browser panels with widgets corresponding to elements in the asset folder
		*/
		void Fill();

		/**
		* Clear the asset browser widgets
		*/
		void Clear();

		/**
		* Refresh the asset browser widgets (Clear + Fill)
		*/
		void Refresh();

	private:
		void ParseFolder(FEditorUI::Widgets::Layout::TreeNode& p_root, const std::filesystem::directory_entry& p_directory, bool p_isEngineItem, bool p_scriptFolder = false);
		void ConsiderItem(FEditorUI::Widgets::Layout::TreeNode* p_root, const std::filesystem::directory_entry& p_entry, bool p_isEngineItem, bool p_autoOpen = false, bool p_scriptFolder = false);

	public:
		static const std::string __FILENAMES_CHARS;

	private:
		std::string m_engineAssetFolder;
		std::string m_projectAssetFolder;
		std::string m_projectScriptFolder;
		FEditorUI::Widgets::Layout::Group* m_assetList;
		std::unordered_map<FEditorUI::Widgets::Layout::TreeNode*, std::string> m_pathUpdate;
	};
}
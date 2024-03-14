/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FEditorUI/Panels/PanelMenuBar.h>
#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Menu/MenuItem.h>

namespace FEditor::Panels
{
	class MenuBar : public FEditorUI::Panels::PanelMenuBar
	{
		using PanelMap = std::unordered_map<std::string, std::pair<std::reference_wrapper<FEditorUI::Panels::PanelWindow>, std::reference_wrapper<FEditorUI::Widgets::Menu::MenuItem>>>;

	public:
		/**
		* Constructor
		*/
		MenuBar();
		
		/**
		* Check inputs for menubar shortcuts
		* @param p_deltaTime
		*/
		void HandleShortcuts(float p_deltaTime);

		/**
		* Register a panel to the menu bar window menu
		*/
		void RegisterPanel(const std::string& p_name, FEditorUI::Panels::PanelWindow& p_panel);

	private:
		void CreateFileMenu();
		void CreateBuildMenu();
		void CreateWindowMenu();
		void CreateActorsMenu();
		void CreateResourcesMenu();
		void CreateSettingsMenu();
		void CreateLayoutMenu();
		void CreateHelpMenu();

		void UpdateToggleableItems();
		void OpenEveryWindows(bool p_state);

	private:
		PanelMap m_panels;

		FEditorUI::Widgets::Menu::MenuList* m_windowMenu = nullptr;
	};
}
/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvRendering/Core/Renderer.h>
#include <FWindow/Context/Device.h>
#include <FWindow/Window.h>
#include <OvRendering/Context/Driver.h>
#include <FEditorUI/Core/UIManager.h>
#include <FEditorUI/Panels/PanelWindow.h>

namespace FEditor::Core
{
	/**
	* A simple panel that allow the user to select the project to launch
	*/
	class ProjectHub
	{
	public:
		/**
		* Constructor
		*/
		ProjectHub();

		/**
		* Run the project hub logic
		*/
		std::tuple<bool, std::string, std::string> Run();

		/**
		* Setup the project hub specific context (minimalist context)
		*/
		void SetupContext();

		/**
		* Register the project (identified from the given path) into the project hub
		* @param p_path
		*/
		void RegisterProject(const std::string& p_path);

	private:
		std::unique_ptr<FWindow::Context::Device>		m_device;
		std::unique_ptr<FWindow::Window>				m_window;
		std::unique_ptr<OvRendering::Context::Driver>		m_driver;
		std::unique_ptr<OvRendering::Core::Renderer>		m_renderer;
		std::unique_ptr<FEditorUI::Core::UIManager>				m_uiManager;

		FEditorUI::Modules::Canvas m_canvas;
		std::unique_ptr<FEditorUI::Panels::PanelWindow>			m_mainPanel;

		std::string m_projectPath = "";
		std::string m_projectName = "";
		bool m_readyToGo = false;
	};
}
/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditor/Core/Context.h"
#include "FEditor/Core/Editor.h"

namespace FEditor::Core
{
	/**
	* Entry point of FEditor
	*/
	class Application
	{
	public:
		/**
		* Constructor
		* @param p_projectPath
		* @param p_projectName
		*/
		Application(const std::string& p_projectPath, const std::string& p_projectName);

		/**
		* Destructor
		*/
		~Application();

		/**
		* Run the app
		*/
		void Run();

		/**
		* Returns true if the app is running
		*/
		bool IsRunning() const;

	private:
		Context m_context;
		Editor m_editor;
	};
}
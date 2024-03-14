/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once


namespace FEditorUI::Plugins
{
	/**
	* Interface to any plugin of FEditorUI.
	* A plugin is basically a behaviour that you can plug to a widget
	*/
	class IPlugin
	{
	public:
		/**
		* Execute the plugin behaviour
		*/
		virtual void Execute() = 0;

		/* Feel free to store any data you want here */
		void* userData = nullptr;
	};
}
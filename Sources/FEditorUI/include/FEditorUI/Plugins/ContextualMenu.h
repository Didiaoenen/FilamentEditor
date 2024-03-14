/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Plugins/IPlugin.h"
#include "FEditorUI/Internal/WidgetContainer.h"
#include "FEditorUI/Widgets/Menu/MenuList.h"
#include "FEditorUI/Widgets/Menu/MenuItem.h"

namespace FEditorUI::Plugins
{
	/**
	* A simple plugin that will show a contextual menu on right click
	* You can add widgets to a contextual menu
	*/
	class ContextualMenu : public IPlugin, public Internal::WidgetContainer
	{
	public:
		/**
		* Execute the plugin
		*/
		void Execute();

		/**
		* Force close the contextual menu
		*/
		void Close();
	};
}

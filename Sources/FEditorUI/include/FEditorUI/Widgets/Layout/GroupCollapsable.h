/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/Layout/Group.h"

namespace FEditorUI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets and is collapsable
	*/
	class GroupCollapsable : public Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		*/
		GroupCollapsable(const std::string& p_name = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool closable = false;
		bool opened = true;
		FTools::Eventing::Event<> CloseEvent;
		FTools::Eventing::Event<> OpenEvent;
	};
}
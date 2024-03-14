/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/Layout/Group.h"

namespace FEditorUI::Widgets::Menu
{
	/**
	* Widget that behave like a group with a menu display
	*/
	class MenuList : public Layout::Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		* @param p_locked
		*/
		MenuList(const std::string& p_name, bool p_locked = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool locked;
		FTools::Eventing::Event<> ClickedEvent;

	private:
		bool m_opened;
	};
}
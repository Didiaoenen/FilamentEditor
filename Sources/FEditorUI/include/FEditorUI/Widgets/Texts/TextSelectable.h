/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/Texts/Text.h"

namespace FEditorUI::Widgets::Texts
{
	/**
	* Simple widget to display a selectable text on a panel
	*/
	class TextSelectable : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_selected
		* @param p_disabled
		*/
		TextSelectable(const std::string& p_content = "", bool p_selected = false, bool p_disabled = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		bool selected;
		bool disabled;

		FTools::Eventing::Event<bool> ClickedEvent;
		FTools::Eventing::Event<> SelectedEvent;
		FTools::Eventing::Event<> UnselectedEvent;
	};
}
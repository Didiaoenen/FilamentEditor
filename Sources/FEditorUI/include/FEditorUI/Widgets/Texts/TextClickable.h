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
	* Widget to display text on a panel that is also clickable
	*/
	class TextClickable : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		*/
		TextClickable(const std::string& p_content = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		FTools::Eventing::Event<> ClickedEvent;
		FTools::Eventing::Event<> DoubleClickedEvent;
	};
}
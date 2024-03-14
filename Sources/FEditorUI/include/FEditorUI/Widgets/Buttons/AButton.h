/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/AWidget.h"

namespace FEditorUI::Widgets::Buttons
{
	/**
	* Base class for any button widget
	*/
	class AButton : public AWidget
	{
	protected:
		void _Draw_Impl() override = 0;

	public:
		FTools::Eventing::Event<> ClickedEvent;
	};
}
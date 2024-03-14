/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <map>

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/DataWidget.h"

namespace FEditorUI::Widgets::Selection
{
	/**
	* Widget that can display a list of values that the user can select
	*/
	class ComboBox : public DataWidget<int>
	{
	public:
		/**
		* Constructor
		* @param p_currentChoice
		*/
		ComboBox(int p_currentChoice = 0);

	protected:
		void _Draw_Impl() override;

	public:
		std::map<int, std::string> choices;
		int currentChoice;

	public:
		FTools::Eventing::Event<int> ValueChangedEvent;
	};
}
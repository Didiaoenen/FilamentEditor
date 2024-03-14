/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/DataWidget.h"

namespace FEditorUI::Widgets::InputFields
{
	/**
	* Input widget of type string
	*/
	class InputText : public DataWidget<std::string>
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_label
		*/
		InputText(const std::string& p_content = "", const std::string& p_label = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string content;
		std::string label;
		bool selectAllOnClick = false;
		FTools::Eventing::Event<std::string> ContentChangedEvent;
		FTools::Eventing::Event<std::string> EnterPressedEvent;
	};
}
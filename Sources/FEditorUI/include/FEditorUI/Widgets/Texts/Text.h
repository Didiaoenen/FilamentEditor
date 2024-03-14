/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Widgets/AWidget.h"
#include "FEditorUI/Widgets/DataWidget.h"

namespace FEditorUI::Widgets::Texts
{
	/**
	* Simple widget to display text on a panel
	*/
	class Text : public DataWidget<std::string>
	{
	public:
		/**
		* Constructor
		* @param p_content
		*/
		Text(const std::string& p_content = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string content;
	};
}
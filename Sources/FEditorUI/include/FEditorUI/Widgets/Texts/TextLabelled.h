/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Widgets/Texts/Text.h"

namespace FEditorUI::Widgets::Texts
{
	/**
	* Simple widget to display a labelled text on a panel
	*/
	class TextLabelled : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_label
		*/
		TextLabelled(const std::string& p_content = "", const std::string& p_label = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string label;
	};
}
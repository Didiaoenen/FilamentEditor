/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "FEditorUI/Widgets/Buttons/AButton.h"
#include "FEditorUI/Types/Color.h"

namespace FEditorUI::Widgets::Buttons
{
	/**
	* Small button widget
	*/
	class ButtonSmall : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_label
		*/
		ButtonSmall(const std::string& p_label = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;

		Types::Color idleBackgroundColor;
		Types::Color hoveredBackgroundColor;
		Types::Color clickedBackgroundColor;

		Types::Color textColor;
	};
}
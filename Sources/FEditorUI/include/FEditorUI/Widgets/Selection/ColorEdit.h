/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Widgets/DataWidget.h"
#include "FEditorUI/Types/Color.h"

namespace FEditorUI::Widgets::Selection
{
	/**
	* Widget that can open a color picker on click
	*/
	class ColorEdit : public DataWidget<Types::Color>
	{
	public:
		/**
		* Constructor
		* @param p_enableAlpha
		* @param p_defaultColor
		*/
		ColorEdit(bool p_enableAlpha = false, const Types::Color& p_defaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		bool enableAlpha;
		Types::Color color;
		FTools::Eventing::Event<Types::Color&> ColorChangedEvent;
	};
}
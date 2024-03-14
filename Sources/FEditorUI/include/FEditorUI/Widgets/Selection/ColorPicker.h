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
	* Widget that allow the selection of a color with a color picker
	*/
	class ColorPicker : public DataWidget<Types::Color>
	{
	public:
		/**
		* Constructor
		* @param p_enableAlpha
		* @param p_defaultColor
		*/
		ColorPicker(bool p_enableAlpha = false, const Types::Color& p_defaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		bool enableAlpha;
		Types::Color color;
		FTools::Eventing::Event<Types::Color&> ColorChangedEvent;
	};
}
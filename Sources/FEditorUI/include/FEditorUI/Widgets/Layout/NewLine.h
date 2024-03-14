/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Widgets/AWidget.h"

namespace FEditorUI::Widgets::Layout
{
	/**
	* Widget that adds an empty line to the panel
	*/
	class NewLine : public AWidget
	{
	protected:
		void _Draw_Impl() override;
	};
}
/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Widgets/AWidget.h"

namespace FEditorUI::Widgets::Visual
{
	/**
	* Simple widget that display a separator
	*/
	class Separator : public AWidget
	{
	protected:
		void _Draw_Impl() override;
	};
}
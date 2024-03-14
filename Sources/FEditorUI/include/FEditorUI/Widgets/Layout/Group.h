/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include "FEditorUI/Internal/WidgetContainer.h"

namespace FEditorUI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets
	*/
	class Group : public AWidget, public Internal::WidgetContainer
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}
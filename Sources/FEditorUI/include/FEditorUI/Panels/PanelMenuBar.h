/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include <FTools/Eventing/Event.h>

#include "FEditorUI/Panels/APanel.h"
#include "FEditorUI/Widgets/Menu/MenuList.h"

namespace FEditorUI::Panels
{
	/**
	* A simple panel that will be displayed on the top side of the canvas
	*/
	class PanelMenuBar : public APanel
	{
	protected:
		void _Draw_Impl() override;
	};
}
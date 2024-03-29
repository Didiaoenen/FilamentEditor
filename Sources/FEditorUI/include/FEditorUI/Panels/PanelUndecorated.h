/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include "FEditorUI/Panels/APanelTransformable.h"

namespace FEditorUI::Panels
{
	/**
	* A simple panel that is transformable and without decorations (No background)
	*/
	class PanelUndecorated : public APanelTransformable
	{
	public:
		void _Draw_Impl() override;

	private:
		int CollectFlags();
	};
}
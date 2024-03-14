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
	* Simple widget that display a bullet point
	*/
	class Bullet : public AWidget
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}
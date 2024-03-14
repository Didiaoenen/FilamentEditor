/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvMaths/FVector2.h>

#include "FEditorUI/Widgets/AWidget.h"

namespace FEditorUI::Widgets::Layout
{
	/**
	* Dummy widget that takes the given size as space in the panel
	*/
	class Dummy : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_size
		*/
		Dummy(const OvMaths::FVector2& p_size = { 0.0f, 0.0f });

	protected:
		void _Draw_Impl() override;

	public:
		OvMaths::FVector2 size;
	};
}
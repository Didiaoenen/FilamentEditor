/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include <OvMaths/FVector2.h>

#include "FEditorUI/Types/Color.h"
#include "FEditorUI/Widgets/Buttons/AButton.h"

namespace FEditorUI::Widgets::Buttons
{
	/**
	* Button widget of a single color (Color palette element)
	*/
	class ButtonColored : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_label
		* @param p_color
		* @param p_size
		* @param p_enableAlpha
		*/
		ButtonColored(const std::string& p_label = "", const Types::Color& p_color = {}, const OvMaths::FVector2& p_size =OvMaths::FVector2(0.f, 0.f), bool p_enableAlpha = true);

	protected:
		void _Draw_Impl() override;

	public:
		std::string label;
		Types::Color color;
		OvMaths::FVector2 size;
		bool enableAlpha;
	};
}
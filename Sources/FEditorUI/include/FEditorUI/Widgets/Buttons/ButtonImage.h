/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvMaths/FVector2.h>

#include "FEditorUI/Internal/TextureID.h"
#include "FEditorUI/Types/Color.h"
#include "FEditorUI/Widgets/Buttons/AButton.h"

namespace FEditorUI::Widgets::Buttons
{
	/**
	* Button widget with an image
	*/
	class ButtonImage : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @param p_size
		*/
		ButtonImage(uint32_t p_textureID, const OvMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		bool disabled = false;

		FEditorUI::Types::Color background = { 0, 0, 0, 0 };
		FEditorUI::Types::Color tint = { 1, 1, 1, 1 };

		Internal::TextureID textureID;
		OvMaths::FVector2 size;
	};
}
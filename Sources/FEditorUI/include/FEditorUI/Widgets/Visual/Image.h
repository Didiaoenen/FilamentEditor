/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvMaths/FVector2.h>

#include "FEditorUI/Internal/TextureID.h"
#include "FEditorUI/Widgets/AWidget.h"

namespace FEditorUI::Widgets::Visual
{
	/**
	* Simple widget that display an image
	*/
	class Image : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @parma p_size
		*/
		Image(uint32_t p_textureID, const OvMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		Internal::TextureID textureID;
		OvMaths::FVector2 size;
	};
}
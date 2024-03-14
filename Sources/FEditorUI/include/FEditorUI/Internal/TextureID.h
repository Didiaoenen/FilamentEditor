/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <stdint.h>

namespace FEditorUI::Internal
{
	/**
	* Simple union necessary for imgui textureID
	*/
	union TextureID
	{
		uint32_t id;
		void* raw;
	};
}
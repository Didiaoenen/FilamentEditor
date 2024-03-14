/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

namespace FEditorUI::API
{
	/**
	* Interface for any drawable class
	*/
	class IDrawable
	{
	public:
		virtual void Draw() = 0;

	protected:
		virtual ~IDrawable() = default;
	};
}

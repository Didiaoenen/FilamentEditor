/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Texts/TextColored.h>

namespace FEditor::Panels
{
	class FrameInfo : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		FrameInfo
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update frame info information
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

	private:
		FEditorUI::Widgets::Texts::TextColored* m_batchCountText;
		FEditorUI::Widgets::Texts::TextColored* m_instanceCountText;
		FEditorUI::Widgets::Texts::TextColored* m_polyCountText;
		FEditorUI::Widgets::Texts::TextColored* m_vertexCountText;
	};
}
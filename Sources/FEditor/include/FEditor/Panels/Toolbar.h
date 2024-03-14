/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FEditorUI/Widgets/Buttons/ButtonImage.h>
#include <FEditorUI/Panels/PanelWindow.h>

namespace FEditor::Panels
{
	class Toolbar : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Toolbar
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Custom implementation of the draw method
		*/
		void _Draw_Impl() override;

	private:
		FEditorUI::Widgets::Buttons::ButtonImage* m_playButton;
		FEditorUI::Widgets::Buttons::ButtonImage* m_pauseButton;
		FEditorUI::Widgets::Buttons::ButtonImage* m_stopButton;
		FEditorUI::Widgets::Buttons::ButtonImage* m_nextButton;
	};
}
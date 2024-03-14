/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <OvAnalytics/Profiling/Profiler.h>

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Texts/TextColored.h>
#include <FEditorUI/Widgets/Selection/CheckBox.h>
#include <FEditorUI/Widgets/Layout/Group.h>
#include <FEditorUI/Widgets/Layout/Columns.h>
#include <FEditorUI/Widgets/Buttons/Button.h>

namespace FEditor::Panels
{
	class Profiler : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_frequency
		*/
		Profiler
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings,
			float p_frequency
		);

		/**
		* Update profiling information
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

		/**
		* Enable or disable the profiler
		* @param p_value
		* @param p_disableLog
		*/
		void Enable(bool p_value, bool p_disableLog = false);

	private:
		FEditorUI::Types::Color CalculateActionColor(double p_percentage) const;
		std::string GenerateActionString(OvAnalytics::Profiling::ProfilerReport::Action& p_action);

	private:
		enum class EProfilingMode
		{
			DEFAULT,
			CAPTURE
		};

		float m_frequency;
		float m_timer = 0.f;
		float m_fpsTimer = 0.f;
		EProfilingMode m_profilingMode = EProfilingMode::DEFAULT;

		OvAnalytics::Profiling::Profiler m_profiler;

		FEditorUI::Widgets::AWidget* m_separator;
		FEditorUI::Widgets::Buttons::Button* m_captureResumeButton;
		FEditorUI::Widgets::Texts::TextColored* m_fpsText;
		FEditorUI::Widgets::Texts::TextColored* m_elapsedFramesText;
		FEditorUI::Widgets::Texts::TextColored* m_elapsedTimeText;
		FEditorUI::Widgets::Layout::Columns<5>* m_actionList;
	};
}
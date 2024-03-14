/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#pragma once

#include <FEditorUI/Panels/PanelWindow.h>
#include <FEditorUI/Widgets/Plots/PlotLines.h>
#include <FEditorUI/Widgets/Plots/PlotHistogram.h>

namespace OvAnalytics::Hardware { class HardwareInfo; }

namespace FEditor::Panels
{
	class HardwareInfo : public FEditorUI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		* @param p_logFrequency
		* @param p_maxElements
		* @param p_displayMode
		*/
		HardwareInfo
		(
			const std::string& p_title,
			bool p_opened,
			const FEditorUI::Settings::PanelWindowSettings& p_windowSettings,
			float p_logFrequency,
			size_t p_maxElements
		);

		/**
		* Destructor
		*/
		~HardwareInfo();

		/**
		* Update hardware info
		* @param p_deltaTime
		*/
		void Update(float p_deltaTime);

	private:
		float p_updateTimer = 0.f;
		float m_logFrequency;
		size_t m_maxElements;
		FEditorUI::Widgets::Plots::APlot* m_cpuUsage;
		FEditorUI::Widgets::Plots::APlot* m_gpuUsage;
		FEditorUI::Widgets::Plots::APlot* m_ramUsage;
		OvAnalytics::Hardware::HardwareInfo* m_hardwareInfo;
	};
}
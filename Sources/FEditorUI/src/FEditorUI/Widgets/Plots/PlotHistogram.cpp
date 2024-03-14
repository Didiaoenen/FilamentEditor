/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditorUI/Widgets/Plots/PlotHistogram.h"
#include "FEditorUI/Internal/Converter.h"

FEditorUI::Widgets::Plots::PlotHistogram::PlotHistogram
(
	const std::vector<float>& p_data,
	float p_minScale,
	float p_maxScale,
	const OvMaths::FVector2& p_size,
	const std::string& p_overlay,
	const std::string& p_label,
	int p_forceHover
) : APlot(p_data, p_minScale, p_maxScale, p_size, p_overlay, p_label, p_forceHover)
{
}

void FEditorUI::Widgets::Plots::PlotHistogram::_Draw_Impl()
{
	ImGui::PlotHistogram((label + m_widgetID).c_str(), data.data(), static_cast<int>(data.size()), 0, overlay.c_str(), minScale, maxScale, Internal::Converter::ToImVec2(size), sizeof(float), forceHover);
}

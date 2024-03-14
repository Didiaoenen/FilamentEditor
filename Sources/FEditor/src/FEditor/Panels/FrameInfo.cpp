/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include "FEditor/Panels/FrameInfo.h"

#include <OvDebug/Logger.h>
#include <FEditorUI/Widgets/Visual/Separator.h>

#include "FEditor/Core/EditorActions.h"
#include "FTools/Utils/Format.h"

using namespace FEditorUI::Panels;
using namespace FEditorUI::Widgets;
using namespace FEditorUI::Types;

FEditor::Panels::FrameInfo::FrameInfo
(
	const std::string& p_title,
	bool p_opened,
	const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	m_batchCountText    = &CreateWidget<Texts::TextColored>("");
	m_instanceCountText = &CreateWidget<Texts::TextColored>("");
	m_polyCountText     = &CreateWidget<Texts::TextColored>("");
	m_polyCountText->lineBreak = false;
	m_vertexCountText = &CreateWidget<Texts::TextColored>("");
}

void FEditor::Panels::FrameInfo::Update(float p_deltaTime)
{
    m_batchCountText->content    = "Batches: "   + FTools::Utils::Format::ReadableNumber(EDITOR_CONTEXT(renderer)->GetFrameInfo().batchCount);
	m_instanceCountText->content = "Instances: " + FTools::Utils::Format::ReadableNumber(EDITOR_CONTEXT(renderer)->GetFrameInfo().instanceCount);
	m_polyCountText->content     = "Polygons: "  + FTools::Utils::Format::ReadableNumber(EDITOR_CONTEXT(renderer)->GetFrameInfo().polyCount);
	m_vertexCountText->content = "Vertices: "  + FTools::Utils::Format::ReadableNumber(EDITOR_CONTEXT(renderer)->GetFrameInfo().vertexCount);
}

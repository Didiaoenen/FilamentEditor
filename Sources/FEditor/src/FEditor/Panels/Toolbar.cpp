/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <FEditorUI/Widgets/Layout/Spacing.h>

#include "FEditor/Panels/Toolbar.h"
#include "FEditor/Core/EditorActions.h"

#include <OvCore/Global/ServiceLocator.h>
#include <OvCore/ResourceManagement/TextureManager.h>

FEditor::Panels::Toolbar::Toolbar
(
	const std::string& p_title,
	bool p_opened,
	const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	std::string iconFolder = ":Textures/Icons/";

	auto& textureManager = OvCore::Global::ServiceLocator::Get<OvCore::ResourceManagement::TextureManager>();

	m_playButton	= &CreateWidget<FEditorUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Play")->id, OvMaths::FVector2{ 20, 20 });
	m_pauseButton	= &CreateWidget<FEditorUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Pause")->id, OvMaths::FVector2{ 20, 20 });
	m_stopButton	= &CreateWidget<FEditorUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Stop")->id, OvMaths::FVector2{ 20, 20 });
	m_nextButton	= &CreateWidget<FEditorUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Next")->id, OvMaths::FVector2{ 20, 20 });

	CreateWidget<FEditorUI::Widgets::Layout::Spacing>(0).lineBreak = false;
	auto& refreshButton	= CreateWidget<FEditorUI::Widgets::Buttons::ButtonImage>(EDITOR_CONTEXT(editorResources)->GetTexture("Button_Refresh")->id, OvMaths::FVector2{ 20, 20 });

	m_playButton->lineBreak		= false;
	m_pauseButton->lineBreak	= false;
	m_stopButton->lineBreak		= false;
	m_nextButton->lineBreak		= false;
	refreshButton.lineBreak		= false;

	m_playButton->ClickedEvent	+= EDITOR_BIND(StartPlaying);
	m_pauseButton->ClickedEvent	+= EDITOR_BIND(PauseGame);
	m_stopButton->ClickedEvent	+= EDITOR_BIND(StopPlaying);
	m_nextButton->ClickedEvent	+= EDITOR_BIND(NextFrame);
	refreshButton.ClickedEvent	+= EDITOR_BIND(RefreshScripts);

	EDITOR_EVENT(EditorModeChangedEvent) += [this](FEditor::Core::EditorActions::EEditorMode p_newMode)
	{
		auto enable = [](FEditorUI::Widgets::Buttons::ButtonImage* p_button, bool p_enable)
		{
			p_button->disabled = !p_enable;
			p_button->tint = p_enable ? FEditorUI::Types::Color{ 1.0f, 1.0f, 1.0f, 1.0f} : FEditorUI::Types::Color{1.0f, 1.0f, 1.0f, 0.15f};
		};

		switch (p_newMode)
		{
		case FEditor::Core::EditorActions::EEditorMode::EDIT:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, false);
			enable(m_nextButton, false);
			break;
		case FEditor::Core::EditorActions::EEditorMode::PLAY:
			enable(m_playButton, false);
			enable(m_pauseButton, true);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		case FEditor::Core::EditorActions::EEditorMode::PAUSE:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		case FEditor::Core::EditorActions::EEditorMode::FRAME_BY_FRAME:
			enable(m_playButton, true);
			enable(m_pauseButton, false);
			enable(m_stopButton, true);
			enable(m_nextButton, true);
			break;
		}
	};

	EDITOR_EXEC(SetEditorMode(FEditor::Core::EditorActions::EEditorMode::EDIT));
}

void FEditor::Panels::Toolbar::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

	FEditorUI::Panels::PanelWindow::_Draw_Impl();

	ImGui::PopStyleVar();
}
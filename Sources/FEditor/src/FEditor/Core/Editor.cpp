/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <OvAnalytics/Profiling/ProfilerSpy.h>
#include <OvPhysics/Core/PhysicsEngine.h>

#include "FEditor/Core/Editor.h"
#include "FEditor/Panels/MenuBar.h"
#include "FEditor/Panels/AssetBrowser.h"
#include "FEditor/Panels/HardwareInfo.h"
#include "FEditor/Panels/Profiler.h"
#include "FEditor/Panels/FrameInfo.h"
#include "FEditor/Panels/Console.h"
#include "FEditor/Panels/Inspector.h"
#include "FEditor/Panels/Hierarchy.h"
#include "FEditor/Panels/SceneView.h"
#include "FEditor/Panels/GameView.h"
#include "FEditor/Panels/AssetView.h"
#include "FEditor/Panels/Toolbar.h"
#include "FEditor/Panels/MaterialEditor.h"
#include "FEditor/Panels/ProjectSettings.h"
#include "FEditor/Panels/AssetProperties.h"

using namespace OvCore::ResourceManagement;
using namespace FEditor::Panels;
using namespace OvRendering::Resources::Loaders;
using namespace OvRendering::Resources::Parsers;

FEditor::Core::Editor::Editor(Context& p_context) : 
	m_context(p_context),
	m_editorRenderer(p_context),
	m_panelsManager(m_canvas),
	m_editorActions(m_context, m_editorRenderer, m_panelsManager)
{
	SetupUI();

	m_context.sceneManager.LoadEmptyLightedScene();
}

FEditor::Core::Editor::~Editor()
{
	m_context.sceneManager.UnloadCurrentScene();
}

void FEditor::Core::Editor::SetupUI()
{
	FEditorUI::Settings::PanelWindowSettings settings;
	settings.closable = true;
	settings.collapsable = true;
	settings.dockable = true;

	m_panelsManager.CreatePanel<FEditor::Panels::MenuBar>("Menu Bar");
	m_panelsManager.CreatePanel<FEditor::Panels::AssetBrowser>("Asset Browser", true, settings, m_context.engineAssetsPath, m_context.projectAssetsPath, m_context.projectScriptsPath);
	m_panelsManager.CreatePanel<FEditor::Panels::HardwareInfo>("Hardware Info", false, settings, 0.2f, 50);
	m_panelsManager.CreatePanel<FEditor::Panels::Profiler>("Profiler", true, settings, 0.25f);
	m_panelsManager.CreatePanel<FEditor::Panels::FrameInfo>("Frame Info", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::Console>("Console", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::Hierarchy>("Hierarchy", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::Inspector>("Inspector", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::SceneView>("Scene View", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::GameView>("Game View", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::AssetView>("Asset View", false, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::Toolbar>("Toolbar", true, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::MaterialEditor>("Material Editor", false, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::ProjectSettings>("Project Settings", false, settings);
	m_panelsManager.CreatePanel<FEditor::Panels::AssetProperties>("Asset Properties", false, settings);

	m_canvas.MakeDockspace(true);
	m_context.uiManager->SetCanvas(m_canvas);
}

void FEditor::Core::Editor::PreUpdate()
{
	PROFILER_SPY("Editor Pre-Update");

	m_context.device->PollEvents();
	m_context.renderer->SetClearColor(0.f, 0.f, 0.f);
	m_context.renderer->Clear();
	m_context.renderer->ClearFrameInfo();
}

void FEditor::Core::Editor::Update(float p_deltaTime)
{
	HandleGlobalShortcuts();
	UpdateCurrentEditorMode(p_deltaTime);
	PrepareRendering(p_deltaTime);
	RenderViews(p_deltaTime);
	UpdateEditorPanels(p_deltaTime);
	RenderEditorUI(p_deltaTime);
	m_editorActions.ExecuteDelayedActions();
}

void FEditor::Core::Editor::HandleGlobalShortcuts()
{
	// If the [Del] key is pressed while an actor is selected and the Scene View or Hierarchy is focused
	if (m_context.inputManager->IsKeyPressed(FWindow::Inputs::EKey::KEY_DELETE) && EDITOR_EXEC(IsAnyActorSelected()) && (EDITOR_PANEL(SceneView, "Scene View").IsFocused() || EDITOR_PANEL(Hierarchy, "Hierarchy").IsFocused()))
	{
		EDITOR_EXEC(DestroyActor(EDITOR_EXEC(GetSelectedActor())));
	}
}

void FEditor::Core::Editor::UpdateCurrentEditorMode(float p_deltaTime)
{
	if (auto editorMode = m_editorActions.GetCurrentEditorMode(); editorMode == EditorActions::EEditorMode::PLAY || editorMode == EditorActions::EEditorMode::FRAME_BY_FRAME)
		UpdatePlayMode(p_deltaTime);
	else
		UpdateEditMode(p_deltaTime);

	{
		PROFILER_SPY("Scene garbage collection");
		m_context.sceneManager.GetCurrentScene()->CollectGarbages();
		m_context.sceneManager.Update();
	}
}

void FEditor::Core::Editor::UpdatePlayMode(float p_deltaTime)
{
	auto currentScene = m_context.sceneManager.GetCurrentScene();
	bool simulationApplied = false;

	{
		PROFILER_SPY("Physics Update");
		simulationApplied = m_context.physicsEngine->Update(p_deltaTime);
	}

	if (simulationApplied)
	{
		PROFILER_SPY("FixedUpdate");
		currentScene->FixedUpdate(p_deltaTime);
	}

	{
		PROFILER_SPY("Update");
		currentScene->Update(p_deltaTime);
	}

	{
		PROFILER_SPY("LateUpdate");
		currentScene->LateUpdate(p_deltaTime);
	}

	{
		PROFILER_SPY("Audio Update");
		m_context.audioEngine->Update();
	}

	ImGui::GetIO().DisableMouseUpdate = m_context.window->GetCursorMode() == FWindow::Cursor::ECursorMode::DISABLED;

	if (m_editorActions.GetCurrentEditorMode() == EditorActions::EEditorMode::FRAME_BY_FRAME)
		m_editorActions.PauseGame();

	if (m_context.inputManager->IsKeyPressed(FWindow::Inputs::EKey::KEY_ESCAPE))
		m_editorActions.StopPlaying();
}

void FEditor::Core::Editor::UpdateEditMode(float p_deltaTime)
{
	if (m_context.inputManager->IsKeyPressed(FWindow::Inputs::EKey::KEY_F5))
		m_editorActions.StartPlaying();
}

void FEditor::Core::Editor::UpdateEditorPanels(float p_deltaTime)
{
	auto& menuBar = m_panelsManager.GetPanelAs<FEditor::Panels::MenuBar>("Menu Bar");
	auto& profiler = m_panelsManager.GetPanelAs<FEditor::Panels::Profiler>("Profiler");
	auto& frameInfo = m_panelsManager.GetPanelAs<FEditor::Panels::FrameInfo>("Frame Info");
	auto& hardwareInfo = m_panelsManager.GetPanelAs<FEditor::Panels::HardwareInfo>("Hardware Info");
	auto& sceneView = m_panelsManager.GetPanelAs<FEditor::Panels::SceneView>("Scene View");

	menuBar.HandleShortcuts(p_deltaTime);

	if (m_elapsedFrames == 1) // Let the first frame happen and then make the scene view the first seen view
		sceneView.Focus();

	if (frameInfo.IsOpened())
	{
		PROFILER_SPY("Frame Info Update");
		frameInfo.Update(p_deltaTime);
	}

	if (profiler.IsOpened())
	{
		PROFILER_SPY("Profiler Update");
		profiler.Update(p_deltaTime);
	}

	if (hardwareInfo.IsOpened())
	{
		PROFILER_SPY("Hardware Info Update");
		hardwareInfo.Update(p_deltaTime);
	}
}

void FEditor::Core::Editor::PrepareRendering(float p_deltaTime)
{
	PROFILER_SPY("Engine UBO Update");
	m_context.engineUBO->SetSubData(m_context.device->GetElapsedTime(), 3 * sizeof(OvMaths::FMatrix4) + sizeof(OvMaths::FVector3));
}

void FEditor::Core::Editor::RenderViews(float p_deltaTime)
{
	auto& assetView = m_panelsManager.GetPanelAs<FEditor::Panels::AssetView>("Asset View");
	auto& sceneView = m_panelsManager.GetPanelAs<FEditor::Panels::SceneView>("Scene View");
	auto& gameView = m_panelsManager.GetPanelAs<FEditor::Panels::GameView>("Game View");

	{
		PROFILER_SPY("Editor Views Update");

		assetView.Update(p_deltaTime);
		gameView.Update(p_deltaTime);
		sceneView.Update(p_deltaTime);
	}

	if (assetView.IsOpened())
	{
		PROFILER_SPY("Asset View Rendering");

		m_context.simulatedLightSSBO->Bind(0);
		assetView.Render();
		m_context.simulatedLightSSBO->Unbind();
	}

	m_context.lightSSBO->Bind(0);

	if (gameView.IsOpened())
	{
		PROFILER_SPY("Game View Rendering");

		gameView.Render();
	}

	if (sceneView.IsOpened())
	{
		PROFILER_SPY("Scene View Rendering");

		sceneView.Render();
	}

	m_context.lightSSBO->Unbind();
}

void FEditor::Core::Editor::RenderEditorUI(float p_deltaTime)
{
	PROFILER_SPY("Editor UI Rendering");

	m_editorActions.GetRenderer().RenderUI();
}

void FEditor::Core::Editor::PostUpdate()
{
	PROFILER_SPY("Editor Post-Update");

	m_context.window->SwapBuffers();
	m_context.inputManager->ClearEvents();
	++m_elapsedFrames;
}
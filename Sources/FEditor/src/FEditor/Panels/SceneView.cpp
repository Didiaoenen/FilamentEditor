/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <FEditorUI/Plugins/DDTarget.h>

#include "FEditor/Core/EditorRenderer.h"
#include "FEditor/Core/EditorActions.h"
#include "FEditor/Panels/SceneView.h"
#include "FEditor/Panels/GameView.h"
#include "FEditor/Settings/EditorSettings.h"

FEditor::Panels::SceneView::SceneView
(
	const std::string& p_title,
	bool p_opened,
	const FEditorUI::Settings::PanelWindowSettings& p_windowSettings
) : AViewControllable(p_title, p_opened, p_windowSettings, true),
	m_sceneManager(EDITOR_CONTEXT(sceneManager))
{
	m_camera.SetClearColor({ 0.098f, 0.098f, 0.098f });
	m_camera.SetFar(5000.0f);

	m_image->AddPlugin<FEditorUI::Plugins::DDTarget<std::pair<std::string, FEditorUI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [this](auto p_data)
	{
		std::string path = p_data.first;

		switch (FTools::Utils::PathParser::GetFileType(path))
		{
		case FTools::Utils::PathParser::EFileType::SCENE:	EDITOR_EXEC(LoadSceneFromDisk(path));			break;
		case FTools::Utils::PathParser::EFileType::MODEL:	EDITOR_EXEC(CreateActorWithModel(path, true));	break;
		}
	};

	OvCore::ECS::Actor::DestroyedEvent += [this](const OvCore::ECS::Actor& actor)
	{
		if (m_highlightedActor.has_value() && m_highlightedActor->get().GetID() == actor.GetID())
		{
			m_highlightedActor = std::nullopt;
		}
	};
}

void FEditor::Panels::SceneView::Update(float p_deltaTime)
{
	AViewControllable::Update(p_deltaTime);

	using namespace FWindow::Inputs;

	if (IsFocused() && !m_cameraController.IsRightMousePressed())
	{
		if (EDITOR_CONTEXT(inputManager)->IsKeyPressed(EKey::KEY_W))
		{
			m_currentOperation = FEditor::Core::EGizmoOperation::TRANSLATE;
		}

		if (EDITOR_CONTEXT(inputManager)->IsKeyPressed(EKey::KEY_E))
		{
			m_currentOperation = FEditor::Core::EGizmoOperation::ROTATE;
		}

		if (EDITOR_CONTEXT(inputManager)->IsKeyPressed(EKey::KEY_R))
		{
			m_currentOperation = FEditor::Core::EGizmoOperation::SCALE;
		}
	}
}

void FEditor::Panels::SceneView::_Render_Impl()
{
	PrepareCamera();

	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();

	uint8_t glState = baseRenderer.FetchGLState();
	baseRenderer.ApplyStateMask(glState);
	HandleActorPicking();
	baseRenderer.ApplyStateMask(glState);
	RenderScene(glState);
	baseRenderer.ApplyStateMask(glState);
}

void FEditor::Panels::SceneView::RenderScene(uint8_t p_defaultRenderState)
{
	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();
	auto& currentScene = *m_sceneManager.GetCurrentScene();
	auto& gameView = EDITOR_PANEL(FEditor::Panels::GameView, "Game View");

	// If the game is playing, and ShowLightFrustumCullingInSceneView is true, apply the game view frustum culling to the scene view (For debugging purposes)
	if (auto gameViewFrustum = gameView.GetActiveFrustum(); gameViewFrustum.has_value() && gameView.GetCamera().HasFrustumLightCulling() && Settings::EditorSettings::ShowLightFrustumCullingInSceneView)
	{
		m_editorRenderer.UpdateLightsInFrustum(currentScene, gameViewFrustum.value());
	}
	else
	{
		m_editorRenderer.UpdateLights(currentScene);
	}

	m_fbo.Bind();

	baseRenderer.SetStencilMask(0xFF);
	baseRenderer.Clear(m_camera);
	baseRenderer.SetStencilMask(0x00);

	m_editorRenderer.RenderGrid(m_cameraPosition, m_gridColor);
	m_editorRenderer.RenderCameras();

	// If the game is playing, and ShowGeometryFrustumCullingInSceneView is true, apply the game view frustum culling to the scene view (For debugging purposes)
	if (auto gameViewFrustum = gameView.GetActiveFrustum(); gameViewFrustum.has_value() && gameView.GetCamera().HasFrustumGeometryCulling() && Settings::EditorSettings::ShowGeometryFrustumCullingInSceneView)
	{
		m_camera.SetFrustumGeometryCulling(gameView.HasCamera() ? gameView.GetCamera().HasFrustumGeometryCulling() : false);
		m_editorRenderer.RenderScene(m_cameraPosition, m_camera, &gameViewFrustum.value());
		m_camera.SetFrustumGeometryCulling(false);
	}
	else
	{
		m_editorRenderer.RenderScene(m_cameraPosition, m_camera);
	}

	m_editorRenderer.RenderLights();

	if (EDITOR_EXEC(IsAnyActorSelected()))
	{
		auto& selectedActor = EDITOR_EXEC(GetSelectedActor());

		if (selectedActor.IsActive())
		{
			m_editorRenderer.RenderActorOutlinePass(selectedActor, true, true);
			baseRenderer.ApplyStateMask(p_defaultRenderState);
			m_editorRenderer.RenderActorOutlinePass(selectedActor, false, true);
		}

		baseRenderer.ApplyStateMask(p_defaultRenderState);
		baseRenderer.Clear(false, true, false);

		int highlightedAxis = -1;

		if (m_highlightedGizmoDirection.has_value())
		{
			highlightedAxis = static_cast<int>(m_highlightedGizmoDirection.value());
		}

		m_editorRenderer.RenderGizmo(selectedActor.transform.GetWorldPosition(), selectedActor.transform.GetWorldRotation(), m_currentOperation, false, highlightedAxis);
	}

	if (m_highlightedActor.has_value())
	{
		m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), true, false);
		baseRenderer.ApplyStateMask(p_defaultRenderState);
		m_editorRenderer.RenderActorOutlinePass(m_highlightedActor.value().get(), false, false);
	}

	m_fbo.Unbind();
}

void FEditor::Panels::SceneView::RenderSceneForActorPicking()
{
	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();

	auto [winWidth, winHeight] = GetSafeSize();

	m_actorPickingFramebuffer.Resize(winWidth, winHeight);
	m_actorPickingFramebuffer.Bind();
	baseRenderer.SetClearColor(1.0f, 1.0f, 1.0f);
	baseRenderer.Clear();
	m_editorRenderer.RenderSceneForActorPicking();

	if (EDITOR_EXEC(IsAnyActorSelected()))
	{
		auto& selectedActor = EDITOR_EXEC(GetSelectedActor());
		baseRenderer.Clear(false, true, false);
		m_editorRenderer.RenderGizmo(selectedActor.transform.GetWorldPosition(), selectedActor.transform.GetWorldRotation(), m_currentOperation, true);
	}

	m_actorPickingFramebuffer.Unbind();
}

bool IsResizing()
{
	auto cursor = ImGui::GetMouseCursor();

	return 
		cursor == ImGuiMouseCursor_ResizeEW ||
		cursor == ImGuiMouseCursor_ResizeNS ||
		cursor == ImGuiMouseCursor_ResizeNWSE ||
		cursor == ImGuiMouseCursor_ResizeNESW ||
		cursor == ImGuiMouseCursor_ResizeAll;;
}

void FEditor::Panels::SceneView::HandleActorPicking()
{
	using namespace FWindow::Inputs;

	auto& inputManager = *EDITOR_CONTEXT(inputManager);

	if (inputManager.IsMouseButtonReleased(EMouseButton::MOUSE_BUTTON_LEFT))
	{
		m_gizmoOperations.StopPicking();
	}

	if (IsHovered() && !IsResizing())
	{
		RenderSceneForActorPicking();

		// Look actor under mouse
		auto [mouseX, mouseY] = inputManager.GetMousePosition();
		mouseX -= m_position.x;
		mouseY -= m_position.y;
		mouseY = GetSafeSize().second - mouseY + 25;

		m_actorPickingFramebuffer.Bind();
		uint8_t pixel[3];
		EDITOR_CONTEXT(renderer)->ReadPixels(static_cast<int>(mouseX), static_cast<int>(mouseY), 1, 1, OvRendering::Settings::EPixelDataFormat::RGB, OvRendering::Settings::EPixelDataType::UNSIGNED_BYTE, pixel);
		m_actorPickingFramebuffer.Unbind();

		uint32_t actorID = (0 << 24) | (pixel[2] << 16) | (pixel[1] << 8) | (pixel[0] << 0);
		auto actorUnderMouse = EDITOR_CONTEXT(sceneManager).GetCurrentScene()->FindActorByID(actorID);
		auto direction = m_gizmoOperations.IsPicking() ? m_gizmoOperations.GetDirection() : EDITOR_EXEC(IsAnyActorSelected()) && pixel[0] == 255 && pixel[1] == 255 && pixel[2] >= 252 && pixel[2] <= 254 ? static_cast<FEditor::Core::GizmoBehaviour::EDirection>(pixel[2] - 252) : std::optional<Core::GizmoBehaviour::EDirection>{};

		m_highlightedActor = {};
		m_highlightedGizmoDirection = {};

		if (!m_cameraController.IsRightMousePressed())
		{
			if (direction.has_value())
			{
				m_highlightedGizmoDirection = direction;

			}
			else if (actorUnderMouse != nullptr)
			{
				m_highlightedActor = std::ref(*actorUnderMouse);
			}
		}

		/* Click */
		if (inputManager.IsMouseButtonPressed(EMouseButton::MOUSE_BUTTON_LEFT) && !m_cameraController.IsRightMousePressed())
		{
			/* Gizmo picking */
			if (direction.has_value())
			{
				m_gizmoOperations.StartPicking(EDITOR_EXEC(GetSelectedActor()), m_cameraPosition, m_currentOperation, direction.value());
			}
			/* Actor picking */
			else
			{

				if (actorUnderMouse)
				{
					EDITOR_EXEC(SelectActor(*actorUnderMouse));
				}
				else
				{
					EDITOR_EXEC(UnselectActor());
				}
			}
		}
	}
	else
	{
		m_highlightedActor = std::nullopt;
	}

	if (m_gizmoOperations.IsPicking())
	{
		auto mousePosition = EDITOR_CONTEXT(inputManager)->GetMousePosition();

		auto [winWidth, winHeight] = GetSafeSize();

		m_gizmoOperations.SetCurrentMouse({ static_cast<float>(mousePosition.first), static_cast<float>(mousePosition.second) });
		m_gizmoOperations.ApplyOperation(m_camera.GetViewMatrix(), m_camera.GetProjectionMatrix(), { static_cast<float>(winWidth), static_cast<float>(winHeight) });
	}
}

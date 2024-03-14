/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <FTools/Time/Clock.h>

#include "FEditor/Core/Application.h"

FEditor::Core::Application::Application(const std::string& p_projectPath, const std::string& p_projectName) :
	m_context(p_projectPath, p_projectName),
	m_editor(m_context)
{
}

FEditor::Core::Application::~Application()
{
}

void FEditor::Core::Application::Run()
{
	FTools::Time::Clock clock;

	while (IsRunning())
	{
		m_editor.PreUpdate();
		m_editor.Update(clock.GetDeltaTime());
		m_editor.PostUpdate();

		clock.Update();
	}
}

bool FEditor::Core::Application::IsRunning() const
{
	return !m_context.window->ShouldClose();
}

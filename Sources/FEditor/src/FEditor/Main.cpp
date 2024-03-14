/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <filesystem>

#include <FTools/Utils/String.h>

#include <OvRendering/Utils/Defines.h>

#include "FEditor/Core/ProjectHub.h"
#include "FEditor/Core/Application.h"

#undef APIENTRY
#include "Windows.h"

FORCE_DEDICATED_GPU

/**
* When FilamentEditor is launched from a project file, we should consider the executable path as
* the current working directory
* @param p_executablePath
*/
void UpdateWorkingDirectory(const std::string& p_executablePath)
{
	if (!IsDebuggerPresent())
	{
		std::filesystem::current_path(FTools::Utils::PathParser::GetContainingFolder(p_executablePath));
	}
}

int main(int argc, char** argv);
static void TryRun(const std::string& projectPath, const std::string& projectName);

#ifndef _DEBUG
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	main(__argc, __argv);
}
#endif

int main(int argc, char** argv)
{
	UpdateWorkingDirectory(argv[0]);

	bool ready = false;
	std::string projectPath;
	std::string projectName;

	{
		FEditor::Core::ProjectHub hub;

		if (argc < 2)
		{
			// No project file given as argument ==> Open the ProjectHub
			std::tie(ready, projectPath, projectName) = hub.Run();
		}
		else
		{
			// Project file given as argument ==> Open the project
			std::string projectFile = argv[1];

			if (FTools::Utils::PathParser::GetExtension(projectFile) == "ovproject")
			{
				ready = true;
				projectPath = FTools::Utils::PathParser::GetContainingFolder(projectFile);
				projectName = FTools::Utils::PathParser::GetElementName(projectFile);
				FTools::Utils::String::Replace(projectName, ".ovproject", "");
			}

			hub.RegisterProject(projectPath);
		}
	}

	if (ready)
		TryRun(projectPath, projectName);

	return EXIT_SUCCESS;
}

static void TryRun(const std::string& projectPath, const std::string& projectName)
{
	auto errorEvent =
		[](FWindow::Context::EDeviceError, std::string errMsg)
		{
			errMsg = "FilamentEditor requires OpenGL 4.3 or newer.\r\n" + errMsg;
			MessageBox(0, errMsg.c_str(), "FilamentEditor", MB_OK | MB_ICONSTOP);
		};

	std::unique_ptr<FEditor::Core::Application> app;

	try
	{
		auto listenerId = FWindow::Context::Device::ErrorEvent += errorEvent;
		app = std::make_unique<FEditor::Core::Application>(projectPath, projectName);
		FWindow::Context::Device::ErrorEvent -= listenerId;
	}
	catch (...) {}

	if (app)
		app->Run();
}

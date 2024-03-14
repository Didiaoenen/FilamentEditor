project "FEditor"
	language "C++"
	cppdialect "C++17"
	files { "**.h", "**.inl","**.cpp", "**.rc" }
	includedirs { "include", dependdir .. "glfw/include",
	"%{wks.location}/FTools/include", "%{wks.location}/FEditorUI/include", "%{wks.location}/FWindow/include" }

	libdirs { dependdir .. "glfw/lib" }
	links { "glfw3dll", "opengl32", "FTools", "FEditorUI", "FWindow" }

	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	characterset ("MBCS")
	debugdir "%{wks.location}/../../Build/%{cfg.buildcfg}"

	postbuildcommands {
		"for /f \"delims=|\" %%i in ('dir /B /S \"%{wks.location}..\\..\\Dependencies\\*.dll\"') do xcopy /Q /Y \"%%i\" \"%{wks.location}..\\..\\Bin\\%{cfg.buildcfg}\\%{prj.name}\"",

		"xcopy \"%{wks.location}\\..\\..\\Resources\\Engine\\*\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Data\\Engine\" /y /i /r /e /q",
		"xcopy \"%{wks.location}\\..\\..\\Resources\\Editor\\*\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Data\\Editor\" /y /i /r /e /q",
		"xcopy \"%{prj.location}\\Layout.ini\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Config\\\" /y /i",

		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Debug\\%{prj.name}\\*.exe\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Debug\\%{prj.name}\\*.dll\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Release\\%{prj.name}\\*.exe\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Release\\%{prj.name}\\*.dll\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",

		"EXIT /B 0"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"
		kind "ConsoleApp"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
		kind "WindowedApp"
project "HRTest"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    postbuildcommands
	{
	    ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/HRRuntime/\"")
	}

	-- includedirs
	-- {
    --     "%{wks.location}/HRLib/src"
	-- }

    -- links
	-- {
	-- 	"HRLib"
	-- }

	filter "system:windows"
		systemversion "latest"

		defines
		{
            "HRT_PLATFORM_WINDOWS",
			"HRT_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "HRT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HRT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HRT_DIST"
		runtime "Release"
		optimize "on"

include "./thirdparty/premake/premake_customization/solution_items.lua"

workspace "HotReloader"
	architecture "x86_64"
	startproject "HRRuntime"

	configurations
	{
		"Debug",
		"Release",	
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "HRRuntime"
include "HRLib"
include "HRTest"

newaction
{
	trigger = "clean",
	description = "Cleans the generated projected files, binaries and intermediates",
	execute = function()
		print("Removing binaries...")
		os.rmdir("**bin")
		print("Removing intermediate files...")
		os.rmdir("**bin-int")
		print("Removing project files...")
		os.remove("**.sln")
		os.remove("**.vcxproj")
		os.remove("**.vcxproj.filters")
		os.remove("**.vcxproj.user")
		os.remove("**Makefile")
		print("Done")
		end
}

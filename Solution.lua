include "3rd-Party/Build/Modules.lua"

workspace "Hedron"
    defines { "SOLUTION_NAME=Hedron" }
    architecture "x64"
    configurations { "Debug", "Release", "Distribution" }
    buildoptions "/utf-8"
    flags { "MultiProcessorCompile" }
    startproject "Nexus"
    systemversion "latest"

    includedirs { "Source" }
    debugdir "%{wks.location}/Build/%{cfg.buildcfg}"
    objdir "%{wks.location}/Cache/%{prj.name}/%{cfg.buildcfg}"
    targetdir "Build/%{cfg.buildcfg}"
	
    Headers = {}
    Headers["Library"] = "%{wks.location}/Source/Library"

    Library = {}
    Package = {}
    
    include "Source/Projects.lua"
    
    group "3rd-Party"
        include "3rd-Party/3rd-Party.lua"
    group ""
 
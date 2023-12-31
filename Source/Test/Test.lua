﻿project "Test"
    defines { "PROJECT_NAME=Test" }
    language "C++"
    characterset "Unicode"
    conformancemode "true"
    cdialect "C17"
    cppdialect "C++latest"
    cppmodules "true"
    buildstlmodules "true"
    externalanglebrackets "on"
    externalwarnings "Off"
    nativewchar "on"
    scanformoduledependencies "on"
    staticruntime "on"
    toolset "msc"
    warnings "Extra"
	
    debugdir "%{wks.location}/Build/%{cfg.buildcfg}"
    dependson { "Vite" }
    entrypoint "mainCRTStartup"
    files { "**.h", "**.cpp", "**.cppm", "**.cxx", "**.inl", "**.ixx", "**.lua" }
    postbuildcommands {
        "robocopy /mir /nfl /ndl /njh /njs /np /r:2 /w:1 \"%{wks.location}Assets\" \"%{cfg.targetdir}/Assets\"",
        "robocopy /mir /nfl /ndl /njh /njs /np /r:2 /w:1 \"%{wks.location}Data\" \"%{cfg.targetdir}/Data\"",
        "exit /b 0",
    }
    
    externalincludedirs {
	    "%{Headers.ThirdParty}"
    }
    includedirs {
        "%{Headers.Library}"
    }
    links {
        "Vite"
    }

    filter { "configurations:Debug" }
        kind "ConsoleApp"
        defines { "_DEBUG" }
        runtime "Debug"
        --sanitize { "Address", "Fuzzer" }
        symbols "on"
    
    filter { "configurations:Distribution" }
        kind "WindowedApp"
        defines { "NDEBUG" }
        optimize "on"
        runtime "Release"
        --sanitize { "Address", "Fuzzer" }
        symbols "on"

    filter { "configurations:Release" }
        kind "WindowedApp"
        defines { "NDEBUG" }
        optimize "on"
        runtime "Release"
        symbols "off"
    
    filter { }

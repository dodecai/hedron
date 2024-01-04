﻿project "Vite"
    defines { "PROJECT_NAME=Vite" }
    kind "StaticLib"
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
    files { "**.h", "**.cpp", "**.cppm", "**.cxx", "**.inl", "**.ixx", "**.lua", "**.natvis", "**.rc" }
    postbuildcommands {
        "copy /b /y \"%{Package.ShaderC}\" \"%{cfg.targetdir}/\"",
        "exit /b 0",
    }
    
    externalincludedirs {
	    "%{Headers.assimp}",
	    "%{Headers.DearImGui}",
	    "%{Headers.EnTT}",
	    "%{Headers.FreeType}",
	    "%{Headers.glad}",
	    "%{Headers.glm}",
	    "%{Headers.MSDFAtlasGen}",
	    "%{Headers.MSDFgen}",
	    "%{Headers.MSDFgen}/msdfgen",
	    "%{Headers.stb}",
        "%{Headers.yamlcpp}",
	    "%{Headers.zlib}",
        
        "%{Headers.ShaderC}",
        "%{Headers.Vulkan}",
        "%{Headers.VulkanVideo}",

        "%{Headers.LibPHX}",
        "%{Headers.LibPHXext}",
    }
    includedirs {
	    "%{Headers.Library}",
    }
    links {
        "assimp",
        "DearImGui",
        "FreeType",
        "Glad",
        "MSDFgen",
        "MSDF-Atlas-Gen",
        "yaml-cpp",

        "%{Library.ShaderC}",
	    --"%{Library.Vulkan}",

        "LibPHX",
    }

    filter { "files: **.natvis "}
        buildaction "Natvis"

    filter { "configurations:Debug" }
        defines { "_DEBUG" }
        runtime "Debug"
        --sanitize { "Address", "Fuzzer" }
        symbols "on"
    
    filter { "configurations:Distribution" }
        defines { "NDEBUG" }
        optimize "on"
        runtime "Release"
        --sanitize { "Address", "Fuzzer" }
        symbols "on"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "on"
        runtime "Release"
        symbols "off"
    
    filter { }

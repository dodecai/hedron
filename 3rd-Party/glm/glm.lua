﻿project "glm"
	kind "StaticLib"
	language "C++"
    characterset "Unicode"
    conformancemode "true"
    cdialect "C17"
	cppdialect "C++20"
    scanformoduledependencies "on"
    staticruntime "on"
    toolset "msc"
    warnings "Default"

	files {
		"include/**",
        "glm.lua",
	}

    includedirs {
        "include",
    }

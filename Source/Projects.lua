solutionitems {
    ["Assets"] = {
        ["Fonts"] = {
        },
        ["Icons"] = {
            "Assets/Icons/*.ico",
        },
        ["Logos"] = {
            "Assets/Logos/*",
        },
        ["Models"] = {
        },
        ["Shaders"] = {
        },
        ["Sounds"] = {
        },
        ["Textures"] = {
        },
    },
    ["Build"] = {
        "3rd-Party/Build/Modules.lua",
        "3rd-Party/3rd-Party.lua",
        "Source/Projects.lua",
        "Solution.lua",
    },
    ["Config"] = {
        ".editorconfig",
        ".git*",
        "Source/Settings.h",
        "vcpkg.json",
    },
    ["Data"] = {
        "Data/*",
    },
    ["Manual"] = {
        ["3rd-Party"] = {
            "3rd-Party/*.md",
        },
        "Manual/*",
    },
    ["Scripts"] = {
        "Scripts/*",
        "Prepare.bat",
    },
    "Contributing.md",
    "License",
    "ReadMe.md",
    "Security.md",
}

filter { "configurations:Debug" }
    defines { "APP_MODE_DEBUG" }

filter { "configurations:Release" }
    defines { "APP_MODE_RELEASE" }
    
filter { "configurations:Distribution" }
    defines { "APP_MODE_DISTRIBUTION" }
    
filter {}

--include "App/App.lua"
--include "Game/Game.lua"
include "Library/Library.lua"
--include "Modules/Modules.lua"
include "Test/Test.lua"
include "Vivid/Vivid.lua"

solutionitems {
    ["Assets"] = {
        ["Fonts"] = {
            ["Dosis"] = {
                "Assets/Fonts/Dosis/*",
            },
            ["Exo2"] = {
                "Assets/Fonts/Exo2/*",
            },
            ["FiraMono"] = {
                "Assets/Fonts/FiraMono/*",
            },
            ["Iceland"] = {
                "Assets/Fonts/Iceland/*",
            },
            ["NovaFlat"] = {
                "Assets/Fonts/NovaFlat/*",
            },
            ["NovaSquare"] = {
                "Assets/Fonts/NovaSquare/*",
            },
            ["Oswald"] = {
                "Assets/Fonts/Oswald/*",
            },
            ["Play"] = {
                "Assets/Fonts/Play/*",
            },
            ["Rajdhani"] = {
                "Assets/Fonts/Rajdhani/*",
            },
            ["Roboto"] = {
                "Assets/Fonts/Roboto/*",
            },
            ["Share"] = {
                "Assets/Fonts/Share/*",
            },
            ["ShareTech"] = {
                "Assets/Fonts/ShareTech/*",
            },
            ["ShareTechMono"] = {
                "Assets/Fonts/ShareTechMono/*",
            },
            ["TitilliumWeb"] = {
                "Assets/Fonts/TitilliumWeb/*",
            },
            ["Ubuntu"] = {
                "Assets/Fonts/Ubuntu/*",
            },
        },
        ["Icons"] = {
            "Assets/Icons/*.ico",
        },
        ["Logos"] = {
            "Assets/Logos/*",
        },
        ["Models"] = {
            ["Cone"] = {
                "Assets/Meshes/Cone/*",
            },
            ["Cube"] = {
                "Assets/Meshes/Cube/*",
            },
            ["Cylinder"] = {
                "Assets/Meshes/Cylinder/*",
            },
            ["Monkey"] = {
                "Assets/Meshes/Monkey/*",
            },
            ["Plane"] = {
                "Assets/Meshes/Plane/*",
            },
            ["Sphere"] = {
                "Assets/Meshes/Sphere/*",
            },
            ["Torus"] = {
                "Assets/Meshes/Torus/*",
            },
        },
        ["Shaders"] = {
            ["Debug"] = {
                "Assets/Shaders/Debug/*",
            },
            ["Defaults"] = {
                "Assets/Shaders/Defaults/*",
            },
            ["Materials"] = {
                "Assets/Shaders/Materials/*",
            },
            ["Meshes"] = {
                "Assets/Shaders/Meshes/*",
            },
            ["PostProcessing"] = {
                "Assets/Shaders/PostProcessing/*",
            },
            ["Sprites"] = {
                "Assets/Shaders/Sprites/*",
            },
            ["UI"] = {
                "Assets/Shaders/UI/*",
            },
            "Assets/Shaders/*",
        },
        ["Sounds"] = {
            "Assets/Sounds/*.mp3",
            "Assets/Sounds/*.wav",
        },
        ["Textures"] = {
            "Assets/Textures/*.png",
            "Assets/Textures/*.tga",
        },
    },
    ["Build"] = {
        "3rd-Party/Build/Modules.lua",
        "3rd-Party/3rd-Party.lua",
        "Source/Projects.lua",
        "Solution.lua",
    },
    ["Config"] = {
        ".clang-*",
        ".editorconfig",
        ".git*",
        "Source/Settings.h",
        "vcpkg.json",
    },
    ["Data"] = {
        "Data/*",
    },
    ["Guide"] = {
        ["3rd-Party"] = {
            "3rd-Party/*.md",
        },
        ["Concept"] = {
            "Guide/Concept/*",
        },
        "Guide/*",
    },
    ["Scripts"] = {
        "Scripts/*",
        "Prepare.bat",
    },
    ["User"] = {
        "User/*",
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

include "Vite/Vite.lua"
include "Nexus/Nexus.lua"
include "Vivid/Vivid.lua"
include "Gaia/Gaia.lua"
include "Phoenix/Phoenix.lua"

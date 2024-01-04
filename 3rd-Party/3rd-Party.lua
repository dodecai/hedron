﻿-- Build Environment

-- Projects
--include "assimp/assimp.lua"
--include "imgui/DearImGui.lua"
include "entt/EnTT.lua"
--include "freetype/FreeType.lua"
include "glad/glad.lua"
--include "glm/glm.lua"
--include "msdfgen/MSDFgen.lua"
--include "msdf-atlas-gen/MSDF-Atlas-Gen.lua"
--include "shaderc/shaderc.lua"
--include "stb/stb.lua"
--include "yaml-cpp/yaml-cpp.lua"
--include "vulkan/vulkan.lua"

--Headers["assimp"] = "%{wks.location}/3rd-Party/assimp/include"
--Headers["DearImGui"] = "%{wks.location}/3rd-Party/imgui/include"
Headers["EnTT"] = "%{wks.location}/3rd-Party/entt/include"
--Headers["FreeType"] = "%{wks.location}/3rd-Party/freetype/include"
Headers["glad"] = "%{wks.location}/3rd-Party/glad/include"
--Headers["glm"] = "%{wks.location}/3rd-Party/glm/include"
--Headers["MSDFAtlasGen"] = "%{wks.location}/3rd-Party/msdf-atlas-gen/include"
--Headers["MSDFgen"] = "%{wks.location}/3rd-Party/msdfgen/include"
--Headers["stb"] = "%{wks.location}/3rd-Party/stb/include"
--Headers["yamlcpp"] = "%{wks.location}/3rd-Party/yaml-cpp/include"
--Headers["zlib"] = "%{wks.location}/3rd-Party/assimp/contrib/zlib"

-- Built-In Headers, Libraries and Packages
--Headers["ShaderC"] = "%{wks.location}/3rd-Party/shaderC/include"
--Headers["Vulkan"] = "%{wks.location}/3rd-Party/vulkan/include"
--Headers["VulkanVideo"] = "%{wks.location}/3rd-Party/vk_video/include"

--Library["ShaderC"] = "%{wks.location}/3rd-Party/shaderc/lib/shaderc_shared.lib"
--Library["Vulkan"] = "%{wks.location}/3rd-Party/vulkan/lib/vulkan-1.lib"
----Library["Vulkan"] = "${VulkanSdkPath}/Lib/vulkan-1.lib"
----Library["VulkanUtils"] = "${VulkanSdkPath}/Lib/VkLayer_utils.lib"

--Package["ShaderC"] = "%{wks.location}3rd-Party\\shaderc\\lib\\shaderc_shared.dll"

-- Test: Phoenix
Headers["LibPHX"] = "%{wks.location}/3rd-Party/LibPHX/include"
Headers["LibPHXext"] = "%{wks.location}/3rd-Party/LibPHX/ext/include"

include "LibPHX/LibPHX.lua"


﻿module;

//#include "Ultra/Core/Core.h"
//
//#if defined(APP_PLATFORM_WINDOWS)
//    #define VK_USE_PLATFORM_WIN32_KHR
//#endif
//
//#include <vulkan/vulkan.hpp>

module Vite.Platform.VKInstance;
//
//#if defined(APP_PLATFORM_WINDOWS)
//    import <Windows.h>;
//#endif
//
//PFN_vkCreateDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT;
//PFN_vkDestroyDebugUtilsMessengerEXT DestroyDebugUtilsMessengerEXT;
//
//// Define a callback to capture the messages
//VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessagerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, [[maybe_unused]] void *userData) {
//    std::string type;
//
//    using Ultra::logger;
//    using Ultra::Log;
//    using Ultra::LogLevel;
//
//    switch ((vk::DebugUtilsMessageSeverityFlagBitsEXT)messageSeverity) {
//        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:      { logger << LogLevel::Error;    break; }
//        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:       { logger << LogLevel::Info;     break; }
//        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:    { logger << LogLevel::Trace;    break; }
//        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:    { logger << LogLevel::Warn;     break; }
//    }
//
//    logger << "GFX::Vulkan[";
//
//    switch ((vk::DebugUtilsMessageTypeFlagBitsEXT)messageType) {
//        case vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral:        { logger << "General"; break; }
//        case vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance:    { logger << "Performance"; break; }
//        case vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation:     { logger << "Validation"; break; }
//    }
//
//    logger << "]: " << LogLevel::Default << callbackData->pMessage << "\n";
//    return false;
//}

namespace Hedron {

//// Default
//VKInstance::VKInstance() {
//    // Application Information
//    vk::ApplicationInfo applicationInfo = {
//        "Application",  VK_MAKE_VERSION(1, 0, 0),
//        "Engine",       VK_MAKE_VERSION(1, 0, 0),
//        /*API*/         VK_API_VERSION_1_2,
//    };
//
//    // Extensions
//    vector<vk::ExtensionProperties> availableExtensions = vk::enumerateInstanceExtensionProperties();
//    vector<const char *> neededExtensions = {
//        VK_KHR_SURFACE_EXTENSION_NAME,
//        #if defined APP_PLATFORM_WINDOWS
//            VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
//        #endif
//        #ifdef APP_MODE_DEBUG
//            VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
//            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
//        #endif
//    };
//    vector<const char *> extensions = GetExtensions(availableExtensions, neededExtensions);
//
//    // Layers
//    vector<vk::LayerProperties> availableLayers = vk::enumerateInstanceLayerProperties();
//    vector<const char *> neededLayers = {
//        #ifdef APP_MODE_DEBUG
//            "VK_LAYER_KHRONOS_validation",
//        #endif
//    };
//    vector<const char *> layers = GetLayers(availableLayers, neededLayers);
//
//    // Instance
//    vk::InstanceCreateInfo intanceCreateInfo = {
//        vk::InstanceCreateFlags(),
//        &applicationInfo,
//        layers,
//        extensions
//    };
//    try {
//        mInstance = vk::createInstance(intanceCreateInfo);
//    } catch (const std::exception& e) {
//        logger << LogLevel::Fatal << ("[GFX::Instance] ", e.what());
//    }
//
//    // Debug
//    #ifdef APP_MODE_DEBUG
//    CreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mInstance, "vkCreateDebugUtilsMessengerEXT");
//    vk::DebugUtilsMessengerCreateInfoEXT messengerCreateInfo = {
//        vk::DebugUtilsMessengerCreateFlagsEXT(),
//        ( // Severities
//            vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo     | 
//            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose  |
//            vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning  |
//            vk::DebugUtilsMessageSeverityFlagBitsEXT::eError 
//        ),
//        ( // Types
//            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral      |
//            vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance  |
//            vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
//        ),
//        DebugMessagerCallback,
//        nullptr,
//    };
//    VkResult result = CreateDebugUtilsMessengerEXT(mInstance, reinterpret_cast<VkDebugUtilsMessengerCreateInfoEXT *>(&messengerCreateInfo), nullptr, &mDebugUtilsMessanger);
//    if (result) { /* ToDo: Check result */ }
//    #endif
//}
//
//VKInstance::~VKInstance() {
//    #ifdef APP_MODE_DEBUG
//    if (mDebugUtilsMessanger) {
//        DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mInstance, "vkDestroyDebugUtilsMessengerEXT");
//        DestroyDebugUtilsMessengerEXT(mInstance, mDebugUtilsMessanger, nullptr);
//    }
//    #endif
//    if (mInstance) {
//        mInstance.destroy(nullptr);
//    }
//}
//
//
//// Accessors
//const vk::Instance &VKInstance::Call() const {
//    return mInstance;
//}
//
//
//// Conversions
//VKInstance::operator const vk::Instance&() const  {
//    return mInstance;
//}
//
//
//// Internal
//vector<const char *> VKInstance::GetExtensions(const vector<vk::ExtensionProperties> &available, const vector<const char *> &needed) {
//    vector<const char *> result = {};
//    for (auto const &n : needed) {
//        for (auto const &a : available) {
//            if (string(a.extensionName.data()).compare(n) == 0) {
//                result.emplace_back(n);
//                break;
//            }
//        }
//    }
//    return result;
//}
//
//vector<const char *> VKInstance::GetLayers(const vector<vk::LayerProperties> &available, const vector<const char *> &needed) {
//    vector<const char *> result = {};
//    for (auto const &n : needed) {
//        for (auto const &a : available) {
//            if (string(a.layerName.data()).compare(n) == 0) {
//                result.emplace_back(n);
//                break;
//            }
//        }
//    }
//    return result;
//}

}

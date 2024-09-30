module;

#include "Vite/Base/Bridges/WinAPI.h"

module Vite.Platform.WinDisplay;

import Vite.Base;

namespace Hedron {

WinDisplay::WinDisplay(string id) {
    mProperties.ID = id;

    DEVMODE deviceMode = {};
    auto nativeId = StringToWString(id);
    auto result = EnumDisplaySettings(nativeId.c_str(), ENUM_CURRENT_SETTINGS, &deviceMode);

    auto gcd = std::gcd(deviceMode.dmPelsWidth, deviceMode.dmPelsHeight);
    auto width = deviceMode.dmPelsWidth / gcd;
    auto height = deviceMode.dmPelsHeight / gcd;
    mProperties.AspectRatio = static_cast<float>(width) / height;
    mProperties.AspectRatioString = std::to_string(width) + ":" + std::to_string(height);

    mProperties.BitsPerPixel = static_cast<float>(deviceMode.dmBitsPerPel);
    mProperties.LogicalDPI = static_cast<float>(deviceMode.dmLogPixels);
    mProperties.RefreshRate = static_cast<float>(deviceMode.dmDisplayFrequency);
    mProperties.Orientation = static_cast<float>(deviceMode.dmDisplayOrientation);
    mProperties.Resolution = std::to_string(deviceMode.dmPelsWidth) + "x" + std::to_string(deviceMode.dmPelsHeight);
    mProperties.Size = {
        .Width = static_cast<float>(deviceMode.dmPelsWidth),
        .Height = static_cast<float>(deviceMode.dmPelsHeight),
    };
    ;
}

WinDisplayManager::WinDisplayManager() {
    auto displayCount = GetSystemMetrics(SM_CMONITORS);
    
    DISPLAY_DEVICE displayDevice = {
        .cb = sizeof(DISPLAY_DEVICE),
    };

    auto deviceIndex = 0;
    while (EnumDisplayDevices(nullptr, deviceIndex, &displayDevice, 0)) {
        if (displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
            auto display = CreateScope<WinDisplay>(WStringToString(displayDevice.DeviceName));
            mDisplays.push_back(std::move(display));
        }
        deviceIndex++;
    }


    //MonitorInfo monitorInfo = {};
    //monitorInfo.cbSize = sizeof(MonitorInfo);

    //for (auto i = 0; i < displayCount; i++) {
    //    if (GetMonitorInformation(nullptr, &monitorInfo)) {
    //        auto display = CreateScope<WinDisplay>(WStringToString(monitorInfo.szDevice));
    //        mDisplays.push_back(std::move(display));
    //    }
    //}

    auto test = false;
}

}

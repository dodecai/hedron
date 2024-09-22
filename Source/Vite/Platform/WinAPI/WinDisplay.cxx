module Vite.Platform.WinDisplay;

import Vite.Base;
import Vite.Bridge.WinAPI;

namespace Hedron {

using namespace WinAPI;

WinDisplay::WinDisplay(string id) {
    mProperties.ID = id;

    DeviceMode deviceMode = {};
    auto nativeId = StringToWString(id);
    auto result = Device::EnumDisplaySettings(nativeId.c_str(), gEnumerateCurrentSettings, &deviceMode);

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
    auto displayCount = WinAPI::System::GetMetrics(SystemMetrics::ScreenCount);
    
    DisplayDevice displayDevice = {
        .cb = sizeof(DisplayDevice),
    };

    auto deviceIndex = 0;
    while (Device::EnumDisplayDevices(nullptr, deviceIndex, &displayDevice, 0)) {
        if (displayDevice.StateFlags & (int)DisplayDeviceState::Attached) {
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

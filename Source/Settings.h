#pragma once

///
/// Properties
///

// Application Information (the solution name will be replaced by preprocessor!)
export namespace SOLUTION_NAME {

// Information
inline constexpr auto AppCaption        = "Ultra Spectra";
inline constexpr auto AppDescription    = "Game Engine Framework";
inline constexpr auto AppRelease        = "2023-07-01";
inline constexpr auto AppVersion        = "0.0.0";
inline constexpr auto AppVersionMajor   = 0u;
inline constexpr auto AppVersionMinor   = 0u;
inline constexpr auto AppVersionPatch   = 0u;

// Switches
#ifdef APP_MODE_DEBUG
    inline constexpr bool DebugMode = true;
#else
    inline constexpr bool DebugMode = false;
#endif
#ifdef APP_MODE_RELEASE
    inline constexpr bool ReleaseMode = true;
#else
    inline constexpr bool ReleaseMode = false;
#endif
#ifdef APP_MODE_DISTRIBUTION
    inline constexpr bool DistributionMode = true;
#else
    inline constexpr bool DistributionMode = false;
#endif

}

// These two lines will select the dedicated graphics card on laptops with two graphic cards installed.
extern "C" {
    __declspec(dllexport) unsigned long NvOptimusEnablement = 0x1;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}


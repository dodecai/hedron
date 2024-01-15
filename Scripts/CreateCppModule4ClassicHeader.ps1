param (
    [string] $SourceHeader = ".\3rd-Party\glad\include\glad\gl.h",
    [string] $HeaderPath = "glad/gl.h",
    [string] $HeaderName = "Glad",
    [string] $HeaderDescription = "GL Loader-Generator"
)

### Variables
    $ModuleTemplate = @"
module;

#include "Vite/Base/Platform/Support.h"

#pragma warning(push, 0)
#include <$headerPath>
#if defined(APP_PLATFORM_WINDOWS)
    #pragma comment(lib, "opengl32.lib")
    #include <GL/wglext.h>
#endif
#pragma warning(pop)

export module Vite.Bridge.$HeaderName;

///
/// @brief Bridge: $HeaderName Library
/// @detail GL Loader-Generator
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export {

`ConvertedMacros

}
#pragma warning(pop)

"@

function ConvertMacros([string] $source) {
    $result = ""

    $count = 0
    foreach ($line in $source -split "`r`n") {
        if ($line -match '#define\s+(\w+)\s+((?:"(?:\\.|[^"])*")|(?:0[xX][0-9a-fA-F]+)|(?:0[oO]?[0-7]+)|(\d+))') {
            $name = $Matches[1]
            $value = $Matches[2]
            if ($value -eq "1") { continue }
            $converted = "#undef $name`r`nconstexpr auto $name = $value;`r`n"
            $result += $converted
        }
    }
    return $result
}

### Main
    $SourceContent = Get-Content $SourceHeader -Raw
    $ConvertedMacros = ConvertMacros $SourceContent
    Write-Output ($ModuleTemplate -replace 'ConvertedMacros',$ConvertedMacros)
    
    

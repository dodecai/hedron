module;

#define YAML_CPP_STATIC_DEFINE
#define YAML_CPP_NO_CONTRIB

#pragma warning(push, 0)

#include <yaml-cpp/yaml.h>

#pragma warning(pop)

export module Vite.Bridge.YamlCpp;

///
/// @brief Bridge: YAML-CPP Library
/// @detail YAML Ain't Markup Language - C++ Library
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace YAML {

using YAML::Exception;
using YAML::Emitter;
using YAML::Node;
using YAML::Parser;
using YAML::LoadFile;

}
#pragma warning(pop)

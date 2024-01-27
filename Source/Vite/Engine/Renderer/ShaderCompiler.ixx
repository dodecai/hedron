﻿export module Vite.Renderer.ShaderCompiler;

import Vite.Core;
import Vite.Renderer.Shader;

export namespace Hedron {

namespace ShaderCompiler {

enum ShaderFormat {
    GLSL,
    HLSL,
    SPIRV,
    Undefined,
};

enum ShaderLanguage {
    Vertex,
    TessControl,
    TessEvaluation,
    Geometry,
    Fragment,
    Compute,
    Undefined2,
};

struct InputOptions {
    // All
    ShaderFormat format;
    ShaderLanguage stage;
    bool ignoreErrors;

    // GLSL
    unsigned glslVersion;
    bool es;

    // HLSL
    //unsigned hlhlShaderModel;

    // MSL
    //unsigned metalPlatform;
};

struct OutputOptions {
    // All
    ShaderFormat format;

    // GLSL
    unsigned glslVersion;
    bool es;

    // HLSL
    //unsigned hlhlShaderModel;

    // MSL
    //unsigned metalPlatform;
};

vector<uint32> Compile(const string &name, ShaderType type, const string &source, bool optimize = false);

string CompileToAssembly(const string &name, ShaderType type, const string &source, bool optimize = false);

string PreprocessShader(const string &name, ShaderType type, const string &source);

string Decompile(const string &source);

}

}

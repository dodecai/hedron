module Vite.Platform.VKShader;

namespace Hedron {}

#ifdef OLD_CODE
void VKShader::Compile(ShaderList shaders) {
    for (auto &[stage, code] : shaders) {
        vector<uint32_t> shader {};

        auto cache = "./Data/Cache/Shaders/" + mShaderName + "." + ShaderTypeToString((ShaderType)stage) + ".spirv";
        if (File::Exists(cache)) {
            shader = File::LoadAsBinary(cache);
        } else {
            shader = ShaderCompiler::Compile(mShaderName, (ShaderType)stage, code);

            // Cache Shader
            if (!shader.empty()) {
                File::Write(cache, shader);
            }
        }

        //vk::ShaderModuleCreateInfo createInfo{};
        //createInfo.flags = vk::ShaderModuleCreateFlags(),
        //createInfo.codeSize = shader.size();
        //cretaeInfo.pCode = reinterpret_cast<uint32_t*>(code.data())

        //vk::ShaderModule module;
        //mDevice.CreateShaderModule(createInfo, module);
    }
}


//static ShaderUniformType SPIRTypeToShaderUniformType(spirv_cross::SPIRType type) {
//    switch (type.basetype) {
//        case spirv_cross::SPIRType::Boolean:    return ShaderUniformType::Bool;
//        case spirv_cross::SPIRType::Int:        return ShaderUniformType::Int;
//        case spirv_cross::SPIRType::Float: {
//            switch (type.vecsize) {
//                case 1: return ShaderUniformType::Float; 
//                case 2: return ShaderUniformType::Vec2; 
//                case 3: return ShaderUniformType::Vec3; 
//                case 4: return ShaderUniformType::Vec4; 
//                default: break;
//            }
//            switch (type.veccolumns) {
//                case 3: return ShaderUniformType::Mat3; 
//                case 4: return ShaderUniformType::Vec4; 
//                default: break;
//            }
//        }
//        default: break;
//    }
//    return ShaderUniformType::None;
//}

static inline string GetShaderExtension(vk::ShaderStageFlagBits flag) {
    string result;
    switch (flag) {
        case vk::ShaderStageFlagBits::eVertex: { result += "-vert";   break;  }
        case vk::ShaderStageFlagBits::eFragment: { result += "-frag";   break;  }
        case vk::ShaderStageFlagBits::eGeometry: { result += "-geom";   break;  }
        case vk::ShaderStageFlagBits::eCompute: { result += "-comp";   break;  }
                                          deault: { result += "-x";        break;  }
    }
    return result;
}

static vk::ShaderStageFlagBits ShaderTypeFromString(const std::string &type) {
    if (type == "vertex")   return vk::ShaderStageFlagBits::eVertex;
    if (type == "geometry") return vk::ShaderStageFlagBits::eGeometry;
    if (type == "fragment" ||
        type == "pixel")    return vk::ShaderStageFlagBits::eFragment;
    if (type == "compute")  return vk::ShaderStageFlagBits::eCompute;

    // Unknown Shader
    return vk::ShaderStageFlagBits::eAll;
}

static vk::ShaderStageFlagBits ShaderTypeFromSuffix(const std::string &type) {
    if (type == "vert")     return vk::ShaderStageFlagBits::eVertex;
    if (type == "geom")     return vk::ShaderStageFlagBits::eGeometry;
    if (type == "frag")     return vk::ShaderStageFlagBits::eFragment;
    if (type == "comp")     return vk::ShaderStageFlagBits::eCompute;

    // Unknown Shader
    return vk::ShaderStageFlagBits::eAll;
}
void VKShader::CreateModules() {
    for (auto &[type, source] : mShaderSource) {
        auto shader = sContext->GetDevice()->Call().createShaderModule(
            vk::ShaderModuleCreateInfo(
                vk::ShaderModuleCreateFlags(),
                source.size(),
                reinterpret_cast<const uint32_t *>(source.data())
            )
        );

        vk::PipelineShaderStageCreateInfo createInfo = {
            vk::PipelineShaderStageCreateFlags(),
            type,
            shader,
            "main"
        };

        mShaderStages.push_back(createInfo);
    }
}

void VKShader::Compile(ShaderMap &sources) {
    ShaderCompiler::InputOptions input = {};
    input.format = ShaderCompiler::ShaderFormat::GLSL;
    input.es = false;
    input.glslVersion = 450;

    ShaderCompiler::OutputOptions output = {};
    output.format = ShaderCompiler::ShaderFormat::SPIRV;
    output.es = true;

    for (auto &[type, data] : sources) {
        if (type == vk::ShaderStageFlagBits::eVertex) {
            input.stage = ShaderCompiler::ShaderLanguage::Vertex;
        } else {
            input.stage = ShaderCompiler::ShaderLanguage::Fragment;
        }
        auto result = ShaderCompiler::Compile(data, input, output);
        if (result != "") mShaderSource[type] = result;
    }
}

VKShader::ShaderMap VKShader::Prepare(string &source) {
    ShaderMap shaderSources;

    const char *typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos) {
        size_t eol = source.find_first_of("\r\n", pos);
        // Syntax Error: eol != std::string::npos
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        // Unknown Shader Type type == "vertex" || type == "fragment" || "pixel"

        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        // Syntax Error: nextLinePos != std::string::npos
        pos = source.find(typeToken, nextLinePos);

        shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }

    return shaderSources;
}

#endif

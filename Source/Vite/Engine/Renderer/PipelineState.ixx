export module Vite.Renderer.PipelineState;

export import Vite.Core;
export import Vite.Renderer.Data;
export import Vite.Renderer.Buffer;
export import Vite.Renderer.Shader;

export namespace Hedron {

///
/// @brief Pipeline Properties
///
struct PipelineProperties {
    BlendMode BlendMode = BlendMode::Disabled;
    CullMode CullMode = CullMode::None;
    bool DepthTest = false;
    bool DepthWritable = true;
    bool Wireframe = false;

    VertexBufferLayout Layout;
    Reference<Shader> Shader;
};

/// 
/// @brief Agnostic Pipeline
/// 
class PipelineState {
    /// Default
protected:
    PipelineState(const PipelineProperties &properties): mProperties(properties) {}
public:
    virtual ~PipelineState() = default;
    static Scope<PipelineState> Create(const PipelineProperties &properties);

    /// Methods
    virtual void Apply() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

protected:
    /// Properties
    PipelineProperties mProperties;
    RendererID mPipelineID;
};

}

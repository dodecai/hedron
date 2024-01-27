export module Vite.Platform.GLPipelineState;

import Vite.Renderer.PipelineState;

export namespace Hedron {

class GLPipelineState: public PipelineState {
public:
    /// Default
    GLPipelineState(const PipelineProperties &properties);
    virtual ~GLPipelineState();

    /// Methods
    void Apply() override;
    void Bind() override;
    void Unbind() override;

private:
    void ResetProperties();
    void UpdateProperties();
};

}

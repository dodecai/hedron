module;

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

export module Vite.UIRenderer;

export import Vite.FontRenderer;

import Vite.Core;
import Vite.Renderer.Buffer;
import Vite.Renderer.CommandBuffer;
import Vite.Renderer.PipelineState;
import Vite.Renderer.Shader;
import Vite.Renderer.Texture;
import Vite.Renderer.Viewport;


///
/// @brief UIRenderer: This is a simple ui renderer, nothing more, nothing less.
///
export namespace Hedron {

//class UIRendererNew {
//public:
//    /// Default
//    UIRendererNew() = default;
//    ~UIRendererNew() = default;
//
//    /// Commands
//    void StartFrame() {}
//    void DrawFrame() {}
//    void FinishFrame() {}
//
//private:
//    void Flush() {}
//};


///
/// @brief Renderer
///

class ClipRect {
    struct ClipRectData {
        bool Enabled;
        Position2D Position;
        Size2D Size;
    };

    struct ClipRectTransform {
        float tx, ty;
        float sx, sy;
    };

public:
    static void Push(const Position2D &position, const Size2D &size);
    static void PushCombined(const Position2D &position, const Size2D &size, Viewport *viewport);
    static void PushDisabled();
    static void PushTransform(const Position2D &position, const Size2D &size);
    static void Pop();
    static void PopTransform();

private:
    static void Activate();
    inline static void TransformRectangle(float &x, float &y, float &sx, float &sy);
    static bool Validate();

private:
    inline static Viewport *mViewport = nullptr;

    inline static constexpr int mStackDepth = 128;
    inline static int mCurrentIndex = -1;
    inline static int mCurrentTransformIndex = -1;

    inline static array<ClipRectData, mStackDepth> mRectangle {};
    inline static array<ClipRectTransform, mStackDepth> mTransform {};
};

struct UIComponent {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoordinate;
    float TextureIndex;
    float TilingFactor;
};

struct UIPanelComponent {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 Size;
    float InnerAlpha;
    float Bevel;
    glm::vec2 TextureCoordinate;
};

struct UITextComponent {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoordinate;
    float TextureIndex;
};

struct TextProperties {
    glm::vec4 Color { 1.0f };
    float Kerning = 0.0f;
    float LineSpacing = 0.0f;
};

class UIRenderer: public SteadyObject {
private: // Default
    UIRenderer() {
        // Panel
        {
            SRenderData.PanelShader = Shader::Create("Assets/Shaders/UI/UI.glsl");
            PipelineProperties panelProperties;
            panelProperties.BlendMode = BlendMode::Alpha;
            panelProperties.DepthTest = true;
            panelProperties.Layout = {
                { ShaderDataType::Float3, "aPosition" },
                { ShaderDataType::Float4, "aColor" },
                { ShaderDataType::Float2, "aSize" },
                { ShaderDataType::Float, "aInnerAlpha" },
                { ShaderDataType::Float, "aBevel" },
                { ShaderDataType::Float2, "aTextureCoordinate" },
            };
            SRenderData.PanelPipeline = PipelineState::Create(panelProperties);

            SRenderData.PanelVertexBufferData.reserve(SRenderData.PanelMaxVertices);
            SRenderData.PanelVertexBuffer = Buffer::Create(BufferType::Vertex, nullptr, SRenderData.PanelMaxVertices * sizeof(UIPanelComponent));
            SRenderData.PanelVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.PanelVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.PanelVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
            SRenderData.PanelVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

            uint32_t offset = 0;
            uint32_t *indices = new uint32_t[SRenderData.PanelMaxIndices];
            for (uint32_t i = 0; i < SRenderData.PanelMaxIndices; i += 6) {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;
                offset += 4;
            }
            SRenderData.PanelIndexBuffer = Buffer::Create(BufferType::Index, indices, SRenderData.PanelMaxVertices * sizeof(uint32_t));
            delete[] indices;
        }

        // Component
        {
            SRenderData.ComponentShader = Shader::Create("Assets/Shaders/UI/UIElement.glsl");
            PipelineProperties componentProperties;
            componentProperties.BlendMode = BlendMode::Alpha;
            componentProperties.DepthTest = true;
            componentProperties.Layout = {
                { ShaderDataType::Float3, "aPosition" },
                { ShaderDataType::Float4, "aColor" },
                { ShaderDataType::Float2, "aTextureCoordinate" },
                { ShaderDataType::Float, "aTextureIndex" },
                { ShaderDataType::Float, "aTilingFactor" },
            };
            SRenderData.ComponentPipeline = PipelineState::Create(componentProperties);
            SRenderData.ComponentVertexBufferData.reserve(SRenderData.ComponentMaxVertices);
            SRenderData.ComponentVertexBuffer = Buffer::Create(BufferType::Vertex, nullptr, SRenderData.ComponentMaxVertices * sizeof(UIComponent));
            SRenderData.ComponentVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.ComponentVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.ComponentVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
            SRenderData.ComponentVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

            uint32_t offset = 0;
            uint32_t *indices = new uint32_t[SRenderData.ComponentMaxIndices];
            for (uint32_t i = 0; i < SRenderData.ComponentMaxIndices; i += 6) {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;
                offset += 4;
            }
            SRenderData.ComponentIndexBuffer = Buffer::Create(BufferType::Index, indices, SRenderData.ComponentMaxVertices * sizeof(uint32_t));
            delete[] indices;

            // Textures
            uint32_t whiteTextureData = 0xffffffff;
            SRenderData.WhiteTexture = Texture::Create(TextureProperties(), &whiteTextureData, sizeof(uint32_t));

            int32_t samplers[SRenderData.MaxTextureSlots];
            for (uint32_t i = 0; i < SRenderData.MaxTextureSlots; i++) samplers[i] = i;
            SRenderData.ComponentShader->Bind();
            //SRenderData.ComponentShader->UpdateUniformBuffer("uTextures", (void *)samplers, SRenderData.MaxTextureSlots);
            SRenderData.TextureSlots[0] = SRenderData.WhiteTexture;
        }

        // Text
        {
            SRenderData.TextShader = Shader::Create("Assets/Shaders/UI/UIText.glsl");
            PipelineProperties textProperties;
            textProperties.BlendMode = BlendMode::Alpha;
            textProperties.DepthTest = true;
            textProperties.Layout = {
                { ShaderDataType::Float3, "aPosition" },
                { ShaderDataType::Float4, "aColor" },
                { ShaderDataType::Float2, "aTextureCoordinate" },
                { ShaderDataType::Float, "aTextureIndex" },
            };
            SRenderData.TextPipeline = PipelineState::Create(textProperties);

            SRenderData.TextVertexBufferData.reserve(SRenderData.TextMaxVertices);
            SRenderData.TextVertexBuffer = Buffer::Create(BufferType::Vertex, nullptr, SRenderData.TextMaxVertices * sizeof(UITextComponent));
            SRenderData.TextVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.TextVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
            SRenderData.TextVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
            SRenderData.TextVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

            uint32_t offset = 0;
            uint32_t *indices = new uint32_t[SRenderData.TextMaxIndices];
            for (uint32_t i = 0; i < SRenderData.TextMaxIndices; i += 6) {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;
                offset += 4;
            }
            SRenderData.TextIndexBuffer = Buffer::Create(BufferType::Index, indices, SRenderData.TextMaxVertices * sizeof(uint32_t));
            delete[] indices;

            int32_t samplers[SRenderData.MaxTextureSlots];
            for (uint32_t i = 0; i < SRenderData.MaxTextureSlots; i++) samplers[i] = i;
            SRenderData.TextShader->Bind();
            //SRenderData.TextShader->UpdateUniformBuffer("uFontAtlas", (void *)samplers, SRenderData.MaxTextureSlots);
        }

        SCommandBuffer = CommandBuffer::Create();

        SRenderData.TransformUniformBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(RenderData::TransformUniform));
        SRenderData.TransformUniformBuffer->Bind(0);
        SRenderData.PanelPropertiesUniformBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(RenderData::PanelPropertiesUniform));
        SRenderData.PanelPropertiesUniformBuffer->Bind(1);

        // Legacy
        PipelineProperties properties {};
        properties.BlendMode = BlendMode::Multiply;
        properties.DepthTest = true;
        mPipelineState = PipelineState::Create(properties);
    }
    ~UIRenderer() = default;
    static UIRenderer &Instance() {
        static UIRenderer instance;
        return instance;
    }

public: // Methods
    static void Begin(const Scope<Viewport> &viewport) {
        static auto &initialize = UIRenderer::Instance();
        //initialize.Test();

        mViewport = viewport.get();
        //auto properties = viewport->GetProperties();
        //auto size = Size2D { properties.Width, properties.Height };
    }
    static void Clip(const Position2D &position, const Size2D &size) {
        ClipRect::PushCombined(position, size, Instance().mViewport);
    }
    static void Draw() {
        auto windowWidth = mViewport->Properties().Size.Width;
        auto windowHeight = mViewport->Properties().Size.Height;

        auto &renderer = Instance();
        renderer.SRenderData.Transform.ProjectionMatrix = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f);
        renderer.SRenderData.Transform.ViewMatrix = glm::mat4(1.0f);

        renderer.SRenderData.TransformUniformBuffer->UpdateData(&renderer.SRenderData.Transform, sizeof(RenderData::TransformUniform));
        renderer.SRenderData.PanelPropertiesUniformBuffer->UpdateData(&renderer.SRenderData.PanelProperties, sizeof(RenderData::PanelPropertiesUniform));
    }
    static void DrawBorder(float s, const Position2D &position, const Size2D &size, const Color &color) {
        glm::vec4 colorOld = { color.Red, color.Green, color.Blue, color.Alpha * 1.0f };
        UIRenderer::Instance().DrawRectangle({ position.X, position.Y, 0 }, { size.Width, s }, colorOld);
        UIRenderer::Instance().DrawRectangle({ position.X, position.Y + size.Height - s, 0 }, { size.Width, s }, colorOld);
        UIRenderer::Instance().DrawRectangle({ position.X, position.Y + s, 0 }, { s, size.Height - 2 * s }, colorOld);
        UIRenderer::Instance().DrawRectangle({ position.X + size.Width - s , position.Y + s, 0 }, { s, size.Height - 2 * s }, colorOld);
    }
    static void DrawPanel(const Position2D &position, const Size2D &size, const Color &color, float bevel, float innerAlpha) {
        const float pad = 64.0f;
        float x = position.X - pad;
        float y = position.Y - pad;
        float width = size.Width + 2.0f * pad;
        float height = size.Height + 2.0f * pad;

        UIRenderer::Instance().DrawPanel({ x, y, 0.0f }, { width, height }, { color.Red, color.Green, color.Blue, color.Alpha }, innerAlpha, bevel);
    }
    static void DrawLine(const Position2D &start, const Position2D &end, const Color &color) {
        UIRenderer::Instance().DrawLine({ start.X, start.Y, 0.0f }, { end.X, end.Y, 0.0f }, { color.Red, color.Green, color.Blue, color.Alpha });
    }
    static void DrawRectangle(const Position2D &position, const Size2D &size, const Color &color) {
        UIRenderer::Instance().DrawRectangle({ position.X, position.Y, 0.0f }, { size.Width, size.Height }, { color.Red, color.Green, color.Blue, color.Alpha });
    }
    static void DrawImage(const Position2D &position, const Size2D &size, const Reference<Texture> &image) {
        UIRenderer::Instance().DrawRectangle({ position.X, position.Y, 0.0f }, { size.Width, size.Height }, image, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    static void DrawText(const Position2D &position, const string &text, const Color &color, Font *font) {
    #define OLD_TEXT_RENDERING1
    #ifdef OLD_TEXT_RENDERING
        auto x = std::floor(position.X);
        auto y = std::floor(position.Y);

        string_view view = text;
        auto begin = view.begin();
        auto end = view.end();
        uint32_t lastGlyph = 0;
        
        while (begin != end) {
            uint32_t codepoint = DecodeUtf8(begin, end);
            auto *glyph = font->GetGlyph(codepoint);
            if (!glyph) {
                lastGlyph = 0;
                continue;
            }
            if (lastGlyph) x += font->GetKerning(lastGlyph, glyph->UniqueID);
            lastGlyph = glyph->UniqueID;
            UIRenderer::Instance().DrawRectangle({ x + glyph->X, y + glyph->Y, 0.0f }, { glyph->Width, glyph->Height }, glyph->Texture, { color.Red, color.Green, color.Blue, color.Alpha });
            //UIRenderer::Instance().DrawText({ x + glyph->X, y + glyph->Y, 0.0f }, { glyph->Width, glyph->Height }, glyph->Texture, {color.Red, color.Green, color.Blue, color.Alpha});
            x += glyph->Advance;
        }
    #else
        TextProperties textParams {};
        const auto &geometry = font->GetMSDFData()->FontGeometry;
        const auto &metrics = geometry.getMetrics();
        const auto &size = font->GetMSDFData()->RequestedFontSize;
        const float spaceGlyphAdvance = geometry.getGlyph(' ')->getAdvance();
        auto fontAtlas = font->GetTexture();

        const float texelWidth = 1.0f / fontAtlas->GetProperties().Width;
        const float texelHeight = 1.0f / fontAtlas->GetProperties().Height;
        
        double x = position.X;
        double y = position.Y;
        double fsScale = size / (metrics.ascenderY - metrics.descenderY);
        
        for (size_t i = 0; i < text.size(); i++) {
            char character = text[i];
            if (character == '\r') continue;
            if (character == '\n') {
                x = 0;
                y -= fsScale * metrics.lineHeight + textParams.LineSpacing;
                continue;
            }
            if (character == ' ') {
                float advance = spaceGlyphAdvance;
                if (i < text.size() - 1) {
                    char nextCharacter = text[i + 1];
                    double dAdvance;
                    geometry.getAdvance(dAdvance, character, nextCharacter);
                    advance = (float)dAdvance;
                }

                x += fsScale * advance + textParams.Kerning;
                continue;
            }
            if (character == '\t') {
                x += 4.0f * (fsScale * spaceGlyphAdvance + textParams.Kerning);
                continue;
            }

            auto glyph = geometry.getGlyph(character);
            if (!glyph) glyph = geometry.getGlyph('?');
            if (!glyph) return;

            double atlasLeft;
            double atlasTop;
            double atlasRight;
            double atlasBottom;
            glyph->getQuadAtlasBounds(atlasLeft, atlasBottom, atlasRight, atlasTop);
            auto texCoordMin = glm::vec2(texelWidth, texelHeight) * glm::vec2((float)atlasLeft, (float)atlasTop);
            auto texCoordMax = glm::vec2(texelWidth, texelHeight) * glm::vec2((float)atlasRight, (float)atlasBottom);

            double planeLeft;
            double planeTop;
            double planeRight;
            double planeBottom;
            glyph->getQuadPlaneBounds(planeLeft, planeBottom, planeRight, planeTop);
            auto quadMin = glm::vec2(x, y) + glm::vec2((float)planeLeft, (float)planeBottom) * fsScale;
            auto quadMax = glm::vec2(x, y) + glm::vec2((float)planeRight, (float)planeTop) * fsScale;

            glm::vec3 nativePosition = { x, y, 0.0f };
            glm::vec2 nativeSize = { quadMax.x - quadMin.x, quadMax.y - quadMin.y };
            glm::vec4 nativeColor = { color.Red, color.Green, color.Blue, color.Alpha };

            static size_t once = 0;
            if (once <= 4) {
                LogInfo(R"(
    Character: '{}'
    Predefined          | Calculated
    Position: {}:{}     | {}:{}
    QuadMin:            | {}:{}
    QuadMax:            | {}:{}
    Size:               | {}:{}
                  )",
                  character,
                  x, y, nativePosition.x, nativePosition.y,
                  quadMin.x, quadMin.y,
                  quadMax.x, quadMax.y,
                  nativeSize.x, nativeSize.y
                );
                once++;
            }

            Instance().DrawText(nativePosition, quadMin, quadMax, nativeSize, fontAtlas, texCoordMin, texCoordMax, nativeColor);
            x += glyph->getAdvance() * fsScale;
        }
    #endif
    }
    static void End() {
        Instance().Reset();
    }
    static void Unclip() {
        ClipRect::Pop();
        Instance().Reset();
    }
    static void Test() {
        //Instance().DrawRectangle({ 500.0f, 200.0f, 0.0f }, { 200.0f, 200.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        //Instance().DrawRectangle({ 650.0f, 300.0f, 0.2f }, { 200.0f, 200.0f }, { 1.0f, 0.0f, 1.0f, 0.8f });
    }

private: // Internal Methods
    void DrawPanel(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float innerAlpha, float bevel);
    void DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color);
    void DrawRectangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f));
    void DrawRectangle(const glm::vec3 &position, const glm::vec2 &size, const Reference<Texture> &texture, const glm::vec4 &color = glm::vec4(1.0f), float tiling = 1.0f);
    void DrawText(const glm::vec3 &position, const glm::vec2 &quadMin, const glm::vec2 &quadMax, const glm::vec2 &size, const Reference<Texture> &texture, const glm::vec2 &textureCoordinateMin, const glm::vec2 &textureCoordinateMax, const glm::vec4 &color = glm::vec4(1.0f));
    void Flush();
    void Reset();

private:
    inline static Scope<CommandBuffer> SCommandBuffer {};
    inline static Scope<PipelineState> mPipelineState {};
    inline static Viewport *mViewport {};

    // Properties
    struct RenderData {
        // Limits
        const size_t MaxComponents = 4096;
        const size_t MaxPanels = 4096;
        const size_t MaxTexts = 4096;
        static constexpr uint32_t MaxTextureSlots = 32; // ToDo: RenderDevice::GetCapabilities().MaxTextureUnits

        // UI Panel
        Reference<PipelineState> PanelPipeline;
        Reference<Shader> PanelShader;
        Reference<Buffer> PanelVertexBuffer;
        Reference<Buffer> PanelIndexBuffer;

        const size_t PanelMaxIndices = MaxPanels * 6;
        const size_t PanelMaxVertices = MaxPanels * 4;
        vector<UIPanelComponent> PanelVertexBufferData;
        array<glm::vec4, 4> PanelVertexPositions;

        // UI Component
        Reference<PipelineState> ComponentPipeline;
        Reference<Shader> ComponentShader;
        Reference<Buffer> ComponentVertexBuffer;
        Reference<Buffer> ComponentIndexBuffer;

        const size_t ComponentMaxIndices = MaxComponents * 6;
        const size_t ComponentMaxVertices = MaxComponents * 4;
        vector<UIComponent> ComponentVertexBufferData;
        array<glm::vec4, 4> ComponentVertexPositions;

        // Textures
        uint32_t TextureSlotIndex = 1;
        array<Reference<Texture>, MaxTextureSlots> TextureSlots;
        Reference<Texture> WhiteTexture;

        // Text
        Reference<PipelineState> TextPipeline;
        Reference<Shader> TextShader;
        Reference<Buffer> TextVertexBuffer;
        Reference<Buffer> TextIndexBuffer;

        const size_t TextMaxIndices = MaxTexts * 6;
        const size_t TextMaxVertices = MaxTexts * 4;
        vector<UITextComponent> TextVertexBufferData;
        array<glm::vec4, 4> TextVertexPositions;

        uint32_t TextTextureSlotIndex = 0;
        array<Reference<Texture>, MaxTextureSlots> TextTextureSlots;

        // Transformation
        struct TransformUniform {
            glm::mat4 ProjectionMatrix {};
            glm::mat4 ViewMatrix {};
        } Transform;

        struct PanelPropertiesUniform {
            float Padding { 64.0f };
        } PanelProperties;

        Reference<Buffer> TransformUniformBuffer;
        Reference<Buffer> PanelPropertiesUniformBuffer;

    } SRenderData;
};

}

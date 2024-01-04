﻿export module Vite.SpriteRenderer;

import Vite.Core;
import Vite.Renderer.Camera;
import Vite.Renderer.DesignerCamera;
import Vite.Renderer.PerspectiveCamera;
import Vite.Renderer.OrthographicCamera;
import Vite.Renderer.CommandBuffer;
import Vite.Renderer.RenderDevice;
import Vite.Renderer.Texture;

namespace Hedron {

//// Properties
//struct CircleComponent {
//    glm::vec3 WorldPosition;
//    glm::vec3 LocalPosition;
//    glm::vec4 Color;
//    float Thickness;
//    float Fade;
//};
//
//struct LineComponent {
//    glm::vec3 Position;
//    glm::vec4 Color;
//};
//
//struct QuadComponent {
//    glm::vec3 Position;
//    glm::vec4 Color;
//    glm::vec2 TextureCoordinate;
//    float TextureIndex;
//    float TilingFactor;
//};

}

export namespace Hedron {

//class Renderer2D {
//public:
//    Renderer2D() = default;
//    ~Renderer2D() = default;
//
//    static void Load();
//    static void Dispose();
//
//    static void StartScene(const Camera &camera);
//    static void StartScene(const DesignerCamera &camera);
//    static void StartScene(const PerspectiveCamera &camera);
//    static void StartScene(const OrthographicCamera &camera);
//    static void FinishScene();
//    static void Flush();
//
//    // Primitives
//    static void DrawCircle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f), float thickness = 1.0f, float fade = 0.005f);
//    static void DrawCircle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f), float thickness = 1.0f, float fade = 0.005f);
//    static void DrawCircle(const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f), float thickness = 1.0f, float fade = 0.005f);
//
//    static void DrawLine(const glm::vec2 &start, const glm::vec2 &end, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec4 &color = glm::vec4(1.0f));
//
//    static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawQuad(const glm::mat4 &transform, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//
//    static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float rotation, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRotatedQuad(const glm::mat4 &transform, const float rotation, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const float rotation, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const float rotation, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRotatedQuad(const glm::mat4 &transform, const float rotation, const Reference<Texture> &texture, const float tilingFactor = 1.0f, const glm::vec4 &color = glm::vec4(1.0f));
//
//    static void DrawRect(const glm::vec2 &position, const glm::vec2 &size = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRect(const glm::vec3 &position, const glm::vec2 &size = glm::vec2(1.0f), const glm::vec4 &color = glm::vec4(1.0f));
//    static void DrawRect(const glm::mat4 &transform, const glm::vec4 &color = glm::vec4(1.0f));
//
//    // Statistics
//    struct Statistics {
//        uint32_t DrawCalls = 0;
//        uint32_t Triangles = 0;
//        uint32_t CircleCount = 0;
//        uint32_t LineCount = 0;
//        uint32_t QuadCount = 0;
//
//        uint32_t GetTotalVertexCount() { return (CircleCount + QuadCount) * 4 + LineCount * 2; }
//        uint32_t GetTotalIndexCount() { return (CircleCount + QuadCount) * 6 + LineCount * 2; }
//    };
//    static void ResetStatistics();
//    static Statistics GetStatistics();
//
//private:
//    static void NextBatch();
//    static void FlushAndReset(PrimitiveType primitive = PrimitiveType::Triangle);
//
//    static Scope<CommandBuffer> sCommandBuffer;
//};

}

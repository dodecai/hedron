export module Vite.Renderer.Buffer;

export import Vite.Core;
export import Vite.Renderer.Data;
import Vite.Renderer.Shader;

export namespace Hedron {

///
/// @brief Buffer Data
///
enum class BufferType {
    Vertex,
    Index,
    Staging,
    Uniform,
    Storage,
};

enum class BufferUsage {
    Dynamic,
    Static,
    Stream,
};

///
/// @brief Index Buffer Data
///
template<typename T>
concept index_t = std::same_as<T, uint8> || std::same_as<T, uint16> || std::same_as<T, uint32>;

enum class IndexType {
    Null    = 0,
    UINT8   = sizeof(uint8),
    UINT16  = sizeof(uint16),
    UINT32  = sizeof(uint32)
};

struct IndexProperties {
    uint32_t Count = {};
    IndexType Type = IndexType::UINT32;
};

///
/// @brief Vertex Buffer Data
///
struct VertexBufferElement {
    VertexBufferElement() = default;
    VertexBufferElement(ShaderDataType type, const string &name, bool normalized = false):
        Name(name),
        Type(type),
        Size(ShaderDataTypeSize(type)),
        Offset(0),
        Normalized(normalized) {
    }

    uint32 GetComponentCount() const {
        switch (Type) {
            case ShaderDataType::Bool:	    return 1;
            case ShaderDataType::Bool2:	    return 2;
            case ShaderDataType::Bool3:	    return 3;
            case ShaderDataType::Bool4:	    return 4;
            case ShaderDataType::Float:	    return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Int:	    return 1;
            case ShaderDataType::Int2:	    return 2;
            case ShaderDataType::Int3:	    return 3;
            case ShaderDataType::Int4:	    return 4;
            case ShaderDataType::Mat2:	    return 3;
            case ShaderDataType::Mat3:	    return 3;
            case ShaderDataType::Mat4:	    return 4;
            default:					    return 0;
        }
    }

    string Name;
    ShaderDataType Type;
    uint32 Size;
    uint32 Offset;
    bool Normalized;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() {}
    VertexBufferLayout(const std::initializer_list<VertexBufferElement> &elements): mElements { elements } {
        CalculateOffsetAndStride();
    }

    inline const std::vector<VertexBufferElement> &GetElements() const { return mElements; }
    inline const uint32_t GetStride() const { return mStride; }

    [[nodiscard]] auto begin() { return mElements.begin(); }
    [[nodiscard]] auto end() { return mElements.end(); }
    [[nodiscard]] auto begin() const { return mElements.begin(); }
    [[nodiscard]] auto end() const { return mElements.end(); }

private:
    void CalculateOffsetAndStride() {
        mStride = 0;
        uint32_t offset = 0;
        for (auto &element : mElements) {
            element.Offset = offset;
            offset += element.Size;
            mStride += element.Size;
        }
    }

    vector<VertexBufferElement> mElements;
    uint32_t mStride = 0;
};


/// 
/// @brief Agnostic Buffer
///
/// @example  auto vertexBuffer = Buffer::Create(BufferType::Vertex, vertices, sizeof(vertices);
/// @example  auto indexBuffer = Buffer::Create(BufferType::Index, indices, sizeof(indices));
/// @example  auto uniformBuffer = Buffer::Create(BufferType::Uniform, data, sizeof(data));
///
class Buffer {
    /// Default
protected:
    Buffer(BufferType type, const void *data, size_t size, BufferUsage usage): mType(type), mData(data), mSize(size), mUsage(usage) {}
public:
    virtual ~Buffer() = default;
    static Scope<Buffer> Create(BufferType type, const void *data, size_t size, BufferUsage usage = BufferUsage::Static);

    /// Mutators
    virtual void UpdateData(const void *data, size_t size) = 0;

    /// Methods
    virtual void Bind() const = 0;
    virtual void Bind([[maybe_unused]] uint32_t binding) const {};
    virtual void Unbind() const = 0;

protected:
    /// Properties
    RendererID mBufferID;
    BufferType mType;
    BufferUsage mUsage;
    const void *mData;
    size_t mSize;
};

}

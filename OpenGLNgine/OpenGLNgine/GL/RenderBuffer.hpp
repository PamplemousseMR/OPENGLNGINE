#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/GL/IBindable.hpp"

#include <vector>

namespace GL
{

/// Manages all render buffer format.
enum RENDERBUFFER_FORMAT : GLenum
{
    RF_DEPTH = GL_DEPTH_COMPONENT,
    RF_DEPTH16 = GL_DEPTH_COMPONENT16,
    RF_DEPTH24 = GL_DEPTH_COMPONENT24,
    RF_DEPTH32 = GL_DEPTH_COMPONENT32,
    RF_DEPTH_STENCIL = GL_DEPTH_STENCIL,
    RF_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
    RF_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
    RF_RED = GL_RED,
    RF_RG = GL_RG,
    RF_RGB = GL_RGB,
    RF_RGBA = GL_RGBA,
    RF_R8 = GL_R8,
    RF_R8_SNORM = GL_R8_SNORM,
    RF_R16 = GL_R16,
    RF_R16_SNORM = GL_R16_SNORM,
    RF_RG8 = GL_RG8,
    RF_RG8_SNORM = GL_RG8_SNORM,
    RF_RG16 = GL_RG16,
    RF_RG16_SNORM = GL_RG16_SNORM,
    RF_R3_G3_B2 = GL_R3_G3_B2,
    RF_RGB4 = GL_RGB4,
    RF_RGB5 = GL_RGB5,
    RF_RGB8 = GL_RGB8,
    RF_RGB8_SNORM = GL_RGB8_SNORM,
    RF_RGB10 = GL_RGB10,
    RF_RGB12 = GL_RGB12,
    RF_RGB16_SNORM = GL_RGB16_SNORM,
    RF_RGBA2 = GL_RGBA2,
    RF_RGBA4 = GL_RGBA4,
    RF_RGB5_A1 = GL_RGB5_A1,
    RF_RGBA8 = GL_RGBA8,
    RF_RGBA8_SNORM = GL_RGBA8_SNORM,
    RF_RGB10_A2 = GL_RGB10_A2,
    RF_RGB10_A2UI = GL_RGB10_A2UI,
    RF_RGBA12 = GL_RGBA12,
    RF_RGBA16 = GL_RGBA16,
    RF_SRGB8 = GL_SRGB8,
    RF_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
    RF_R16F = GL_R16F,
    RF_RG16F = GL_RG16F,
    RF_RGB16F = GL_RGB16F,
    RF_RGBA16F = GL_RGBA16F,
    RF_R32F = GL_R32F,
    RF_RG32F = GL_RG32F,
    RF_RGB32F = GL_RGB32F,
    RF_RGBA32F = GL_RGBA32F,
    RF_R11F_G11F_B10F = GL_R11F_G11F_B10F,
    RF_RGB9_E5 = GL_RGB9_E5,
    RF_R8I = GL_R8I,
    RF_R8UI = GL_R8UI,
    RF_R16I = GL_R16I,
    RF_R16UI = GL_R16UI,
    RF_R32I = GL_R32I,
    RF_R32UI = GL_R32UI,
    RF_RG8I = GL_RG8I,
    RF_RG8UI = GL_RG8UI,
    RF_RG16I = GL_RG16I,
    RF_RG16UI = GL_RG16UI,
    RF_RG32I = GL_RG32I,
    RF_RG32UI = GL_RG32UI,
    RF_RGB8I = GL_RGB8I,
    RF_RGB8UI = GL_RGB8UI,
    RF_RGB16I = GL_RGB16I,
    RF_RGB16UI = GL_RGB16UI,
    RF_RGB32I = GL_RGB32I,
    RF_RGB32UI = GL_RGB32UI,
    RF_RGBA8I = GL_RGBA8I,
    RF_RGBA8UI = GL_RGBA8UI,
    RF_RGBA16I = GL_RGBA16I,
    RF_RGBA16UI = GL_RGBA16UI,
    RF_RGBA32I = GL_RGBA32I,
    RF_RGBA32UI = GL_RGBA32UI
};

/**
 * @brief Manages a render buffer object.
 */
class RenderBuffer final : public IBindable
{

public:

    /// Creates a render buffer.
    RenderBuffer();

    /// Destroys the render buffer.
    ~RenderBuffer() override;

    /**
     * @brief Generates a new render buffer and copy the contents of the parameter to the generated one.
     * @param _renderBuffer The render buffer to copy.
     */
    RenderBuffer(const RenderBuffer& _renderBuffer);

    /**
     * @brief Copies the contents of the render buffer to the current one.
     * @param _renderBuffer The render buffer to copy.
     */
    RenderBuffer& operator=(const RenderBuffer& _renderBuffer);

    /// Deleted move constructor.
    RenderBuffer(RenderBuffer&&) = delete;

    /// Deleted move operator.
    RenderBuffer& operator=(RenderBuffer&&) = delete;

    /**
     * @brief Allocates the memory of the render buffer.
     * @param _width The render buffer width.
     * @param _height The render buffer height.
     * @param _format The render buffer format.
     */
    void allocate(int _width, int _height, RENDERBUFFER_FORMAT _format) const;

    /**
     * @brief Allocates the memory of the render buffer.
     * @param _width The render buffer width.
     * @param _height The render buffer height.
     * @param _format The render buffer format.
     * @param _sample The render buffer sample.
     */
    void allocateMultisample(int _width, int _height, RENDERBUFFER_FORMAT _format, int _sample) const;

    /// Binds the render buffer.
    inline void bind() const override;

    /// Unbinds the render buffer.
    inline void unbind() const override;

private:

    /// Automaticaly called one time.
    struct Initializer final
    {
        /// Gets the max size of render buffer.
        Initializer();
    };

    /// Defines the maximum size of a render buffer.
    static GLint s_MAX_SIZE;

    /// Defines the maximum of samples of a render buffer.
    static GLint s_MAX_SAMPLE;

    /// Defines the bind status.
    mutable bool m_isBinded { false };

};

inline void RenderBuffer::bind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    }
}

inline void RenderBuffer::unbind() const
{
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}

}

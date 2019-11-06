#pragma once

#include <assert.h>
#include <vector>

#include "GL/IBindable.hpp"

namespace GL
{

class RenderBuffer : public IBindable
{

public:

    enum RENDERBUFFER_FORMAT : GLenum
    {
        FORMAT_DEPTH = GL_DEPTH_COMPONENT,
        FORMAT_DEPTH16 = GL_DEPTH_COMPONENT16,
        FORMAT_DEPTH24 = GL_DEPTH_COMPONENT24,
        FORMAT_DEPTH32 = GL_DEPTH_COMPONENT32,
        FORMAT_DEPTH_STENCIL = GL_DEPTH_STENCIL,
        FORMAT_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
        FORMAT_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
        FORMAT_RED = GL_RED,
        FORMAT_RG = GL_RG,
        FORMAT_RGB = GL_RGB,
        FORMAT_RGBA = GL_RGBA,
        FORMAT_R8 = GL_R8,
        FORMAT_R8_SNORM = GL_R8_SNORM,
        FORMAT_R16 = GL_R16,
        FORMAT_R16_SNORM = GL_R16_SNORM,
        FORMAT_RG8 = GL_RG8,
        FORMAT_RG8_SNORM = GL_RG8_SNORM,
        FORMAT_RG16 = GL_RG16,
        FORMAT_RG16_SNORM = GL_RG16_SNORM,
        FORMAT_R3_G3_B2 = GL_R3_G3_B2,
        FORMAT_RGB4 = GL_RGB4,
        FORMAT_RGB5 = GL_RGB5,
        FORMAT_RGB8 = GL_RGB8,
        FORMAT_RGB8_SNORM = GL_RGB8_SNORM,
        FORMAT_RGB10 = GL_RGB10,
        FORMAT_RGB12 = GL_RGB12,
        FORMAT_RGB16_SNORM = GL_RGB16_SNORM,
        FORMAT_RGBA2 = GL_RGBA2,
        FORMAT_RGBA4 = GL_RGBA4,
        FORMAT_RGB5_A1 = GL_RGB5_A1,
        FORMAT_RGBA8 = GL_RGBA8,
        FORMAT_RGBA8_SNORM = GL_RGBA8_SNORM,
        FORMAT_RGB10_A2 = GL_RGB10_A2,
        FORMAT_RGB10_A2UI = GL_RGB10_A2UI,
        FORMAT_RGBA12 = GL_RGBA12,
        FORMAT_RGBA16 = GL_RGBA16,
        FORMAT_SRGB8 = GL_SRGB8,
        FORMAT_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
        FORMAT_R16F = GL_R16F,
        FORMAT_RG16F = GL_RG16F,
        FORMAT_RGB16F = GL_RGB16F,
        FORMAT_RGBA16F = GL_RGBA16F,
        FORMAT_R32F = GL_R32F,
        FORMAT_RG32F = GL_RG32F,
        FORMAT_RGB32F = GL_RGB32F,
        FORMAT_RGBA32F = GL_RGBA32F,
        FORMAT_R11F_G11F_B10F = GL_R11F_G11F_B10F,
        FORMAT_RGB9_E5 = GL_RGB9_E5,
        FORMAT_R8I = GL_R8I,
        FORMAT_R8UI = GL_R8UI,
        FORMAT_R16I = GL_R16I,
        FORMAT_R16UI = GL_R16UI,
        FORMAT_R32I = GL_R32I,
        FORMAT_R32UI = GL_R32UI,
        FORMAT_RG8I = GL_RG8I,
        FORMAT_RG8UI = GL_RG8UI,
        FORMAT_RG16I = GL_RG16I,
        FORMAT_RG16UI = GL_RG16UI,
        FORMAT_RG32I = GL_RG32I,
        FORMAT_RG32UI = GL_RG32UI,
        FORMAT_RGB8I = GL_RGB8I,
        FORMAT_RGB8UI = GL_RGB8UI,
        FORMAT_RGB16I = GL_RGB16I,
        FORMAT_RGB16UI = GL_RGB16UI,
        FORMAT_RGB32I = GL_RGB32I,
        FORMAT_RGB32UI = GL_RGB32UI,
        FORMAT_RGBA8I = GL_RGBA8I,
        FORMAT_RGBA8UI = GL_RGBA8UI,
        FORMAT_RGBA16I = GL_RGBA16I,
        FORMAT_RGBA16UI = GL_RGBA16UI,
        FORMAT_RGBA32I = GL_RGBA32I,
        FORMAT_RGBA32UI = GL_RGBA32UI
    };

public:

    RenderBuffer();
    ~RenderBuffer() noexcept final;
    RenderBuffer(const RenderBuffer&);
    RenderBuffer(RenderBuffer&&) = delete;
    RenderBuffer& operator=(const RenderBuffer&);
    RenderBuffer& operator=(RenderBuffer&&) = delete;

    void allocate(int, int, RENDERBUFFER_FORMAT) const;
    void allocateMultisample(int, int, RENDERBUFFER_FORMAT, int) const;

    inline virtual void bind() const noexcept final;
    inline virtual void unbind() const noexcept final;

private:

    static GLint s_maxSize;
    static GLint s_maxSample;
    static bool s_first;

};

inline void RenderBuffer::bind() const noexcept
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void RenderBuffer::unbind() const noexcept
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}


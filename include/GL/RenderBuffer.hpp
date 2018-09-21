#pragma once

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class RenderBuffer : public IGLObject
{

public:

    enum RENDERBUFFER_FORMAT
    {
        FORMAT_RGB = GL_RGB,
        FORMAT_RGBA = GL_RGBA,
        FORMAT_DEPTH = GL_DEPTH_COMPONENT
    };

public:

    RenderBuffer();
    ~RenderBuffer() noexcept;
    RenderBuffer(const RenderBuffer&);
    RenderBuffer(RenderBuffer&&) = delete;
    RenderBuffer& operator=(const RenderBuffer&);
    RenderBuffer& operator=(RenderBuffer&&) = delete;

    void allocate(int, int, RENDERBUFFER_FORMAT) const;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

private:

    static GLint s_maxSize;
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


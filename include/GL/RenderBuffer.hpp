#pragma once

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class RenderBuffer : public IGLObject
{

public:

    RenderBuffer();
    ~RenderBuffer() noexcept;
    RenderBuffer(const RenderBuffer&);
    RenderBuffer(RenderBuffer&&) = delete;
    RenderBuffer& operator=(const RenderBuffer&);
    RenderBuffer& operator=(RenderBuffer&&) = delete;

    void setStorage(int, int) const;

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


#pragma once

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class VertexArrayBuffer : public IGLObject
{

public:

    VertexArrayBuffer();
    ~VertexArrayBuffer() noexcept override;
    VertexArrayBuffer(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer(VertexArrayBuffer&&) = delete;
    VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer& operator=(VertexArrayBuffer&&) = delete;

    inline virtual void bind() const noexcept override;
    inline virtual void unbind() const noexcept override;

};

inline void VertexArrayBuffer::bind() const noexcept
{
    glBindVertexArray(m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexArrayBuffer::unbind() const noexcept
{
    glBindVertexArray(0);
    assert(glGetError() == GL_NO_ERROR);
}

}


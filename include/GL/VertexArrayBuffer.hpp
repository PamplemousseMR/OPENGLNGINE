#pragma once

#include <assert.h>
#include <vector>

#include "GL/IBindable.hpp"

namespace GL
{

class VertexArrayBuffer : public IBindable
{

public:

    VertexArrayBuffer();
    ~VertexArrayBuffer() final;
    VertexArrayBuffer(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer(VertexArrayBuffer&&) = delete;
    VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer& operator=(VertexArrayBuffer&&) = delete;

    inline virtual void bind() const final;
    inline virtual void unbind() const final;

};

inline void VertexArrayBuffer::bind() const
{
    glBindVertexArray(m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexArrayBuffer::unbind() const
{
    glBindVertexArray(0);
    assert(glGetError() == GL_NO_ERROR);
}

}


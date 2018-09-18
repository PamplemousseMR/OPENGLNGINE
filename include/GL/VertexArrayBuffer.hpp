#pragma once

#include <vector>

#include "GL/IGLObject.hpp"

namespace GL
{

class VertexArrayBuffer : public IGLObject
{

public:

    VertexArrayBuffer();
    ~VertexArrayBuffer() noexcept;
    VertexArrayBuffer(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer(VertexArrayBuffer&&) = delete;
    VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;
    VertexArrayBuffer& operator=(VertexArrayBuffer&&) = delete;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

};

inline void VertexArrayBuffer::bind() const noexcept
{
    glBindVertexArray(m_id);
}

inline void VertexArrayBuffer::unbind() const noexcept
{
    glBindVertexArray(0);
}

}


#pragma once

#include <vector>

#include "GL/IBuffer.hpp"

#define BUFFER_OFFSET(i) (static_cast< GLfloat* >(nullptr) + (i))

namespace GL 
{

class VertexBuffer : public IBuffer
{

public:

    VertexBuffer();
    ~VertexBuffer() noexcept;
    VertexBuffer(const VertexBuffer&);
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&);
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const noexcept;
    inline void setLocation(GLuint) const noexcept;
    inline void setAttrib(GLuint, GLint, GLenum, GLboolean, GLsizei, GLint) const noexcept;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

};

template<typename T>
inline void VertexBuffer::setData(const std::vector<T>& _arr) const noexcept
{
    glBufferData(GL_ARRAY_BUFFER, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
}

inline void VertexBuffer::setLocation(GLuint _location) const noexcept
{
    glEnableVertexAttribArray(_location);
}

inline void VertexBuffer::setAttrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalize, GLsizei _stride, GLint _offset) const noexcept
{
    glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
}

inline void VertexBuffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

inline void VertexBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}


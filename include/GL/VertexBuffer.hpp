#pragma once

#include <assert.h>
#include <vector>

#include "GL/IBindable.hpp"

#define BUFFER_OFFSET(i) (static_cast< GLfloat* >(nullptr) + (i))

namespace GL 
{

class VertexBuffer : public IBindable
{

public:

    VertexBuffer();
    ~VertexBuffer() noexcept final;
    VertexBuffer(const VertexBuffer&) noexcept;
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) noexcept;
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const noexcept;
    inline void setLocation(GLuint) const noexcept;
    inline void setAttrib(GLuint, GLint, GLenum, GLboolean, GLsizei, GLint) const noexcept;

    inline virtual void bind() const noexcept final;
    inline virtual void unbind() const noexcept final;
};

template<typename T>
inline void VertexBuffer::setData(const std::vector<T>& _arr) const noexcept
{
    glBufferData(GL_ARRAY_BUFFER, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::setLocation(GLuint _location) const noexcept
{
    glEnableVertexAttribArray(_location);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::setAttrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalize, GLsizei _stride, GLint _offset) const noexcept
{
    glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::bind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::unbind() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}


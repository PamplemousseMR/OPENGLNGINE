#pragma once

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"

#define BUFFER_OFFSET(i) (static_cast< GLfloat* >(nullptr) + (i))

namespace GL 
{

class VertexBuffer : public IGLObject
{

public:

    VertexBuffer();
    ~VertexBuffer() noexcept;
    VertexBuffer(const VertexBuffer&);
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&);
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const;
    inline void setLocation(GLuint) const noexcept;
    inline void setAttrib(GLuint, GLint, GLenum, GLboolean, GLsizei, GLint) const noexcept;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

private:

    static GLint s_maxVertices;
    static bool s_first;

};

template<typename T>
inline void VertexBuffer::setData(const std::vector<T>& _arr) const
{
    if(_arr.size() > s_maxVertices)
    {
        throw std::overflow_error("[VertexBuffer] Too big");
    }
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


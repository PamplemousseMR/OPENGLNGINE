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
    ~VertexBuffer() final;
    VertexBuffer(const VertexBuffer&);
    VertexBuffer(VertexBuffer&&) = delete;
    VertexBuffer& operator=(const VertexBuffer&);
    VertexBuffer& operator=(VertexBuffer&&) = delete;

    template<typename T>
    inline void setData(const std::vector<T>&) const;
    inline void setLocation(GLuint) const;
    inline void setAttrib(GLuint, GLint, GLenum, GLboolean, GLsizei, GLint) const;

    inline virtual void bind() const final;
    inline virtual void unbind() const final;
};

template<typename T>
inline void VertexBuffer::setData(const std::vector<T>& _arr) const
{
    glBufferData(GL_ARRAY_BUFFER, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::setLocation(GLuint _location) const
{
    glEnableVertexAttribArray(_location);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::setAttrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalize, GLsizei _stride, GLint _offset) const
{
    glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}


#include "OpenGLNgine/GL/DataBuffer.hpp"

#include <iostream>

namespace GL
{

GLint DataBuffer::s_MAX_VERTEX_ATTRIBS = 0;

#ifdef GLNGINE_USE_STATE_CACHE
ptrdiff_t DataBuffer::s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
#endif

void DataBuffer::setLocation(unsigned _location)
{
    GLNGINE_ASSERT_IF(_location >= unsigned(s_MAX_VERTEX_ATTRIBS), "Location too hight");
    glEnableVertexAttribArray(_location);
    GLNGINE_CHECK_GL;
}

void DataBuffer::setAttrib(unsigned _location, unsigned _size, DATABUFFER_TYPE _type, bool _normalize, unsigned _stride, unsigned _offset)
{
    GLNGINE_ASSERT_IF(_location >= unsigned(s_MAX_VERTEX_ATTRIBS), "Location too hight");
    GLNGINE_ASSERT_IF(_size != 1 && _size != 2 && _size != 3 && _size != 4, "Size shall be 1, 2, 3 or 4");
    glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
    GLNGINE_CHECK_GL;
}

DataBuffer::DataBuffer(DATABUFFER_TARGET _target) :
    IBindable(),
    m_target(_target)
{
    [[maybe_unused]] static const void* initializer = []()
    {
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &s_MAX_VERTEX_ATTRIBS);
        GLNGINE_CHECK_GL;
        return nullptr;
    } ();

    glGenBuffers(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the buffer");
    }
}

DataBuffer::~DataBuffer()
{
    glDeleteBuffers(1, &m_id);
}

DataBuffer::DataBuffer(const DataBuffer& _buffer) :
    IBindable(_buffer),
    m_target(_buffer.m_target)
{
    glGenBuffers(1, &m_id);

    glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
    glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

    GLint size = 0;
    glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
    if(size != 0)
    {
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
    }

    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    GLNGINE_CHECK_GL;
}

DataBuffer& DataBuffer::operator=(const DataBuffer& _buffer)
{
    if(this != &_buffer)
    {
        glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

        GLint size = 0;
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
        if(size != 0)
        {
            glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
        }

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        GLNGINE_CHECK_GL;
    }
    return *this;
}

void DataBuffer::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add)
    {
        s_cache = add;
        glBindBuffer(m_target, m_id);
    }
#else
    glBindBuffer(m_target, m_id);
#endif
}

void DataBuffer::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_cache != add)
    {
        s_cache = add;
        glBindBuffer(m_target, 0);
    }
#else
    glBindBuffer(m_target, 0);
#endif
}

}

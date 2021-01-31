#include "OpenGLNgine/GL/DataBuffer.hpp"

using namespace std;

namespace GL
{

DataBuffer::DataBuffer(DATABUFFER_TARGET _target) :
    IBindable(),
    m_target(_target)
{
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
}

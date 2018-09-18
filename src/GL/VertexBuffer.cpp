#include "GL/VertexBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    VertexBuffer::VertexBuffer() :
        IBuffer()
    {
        glGenBuffers(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[VertexBuffer] Out of memory");
        }
    }

    VertexBuffer::~VertexBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }

    VertexBuffer::VertexBuffer(const VertexBuffer& _buffer) :
        IBuffer(_buffer)
    {
        glGenBuffers(1, &m_id);

        glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

        GLint size = 0;
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
        if (size != 0)
        {
            glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
            if(glGetError() == GL_OUT_OF_MEMORY )
            {
                throw overflow_error("[VertexBuffer] Out of memory");
            }
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
        }

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    }

    VertexBuffer& VertexBuffer::operator=(const VertexBuffer& _buffer)
    {
        if(this != &_buffer)
        {
            glDeleteBuffers(1, &m_id);

            glGenBuffers(1, &m_id);

            glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
            glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

            GLint size = 0;
            glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
            if (size != 0)
            {
                glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
                if(glGetError() == GL_OUT_OF_MEMORY )
                {
                    throw overflow_error("[VertexBuffer] Out of memory");
                }
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
            }

            glBindBuffer(GL_COPY_READ_BUFFER, 0);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }
        return *this;
    }
}

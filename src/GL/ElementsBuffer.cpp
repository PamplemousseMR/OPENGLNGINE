#include "GL/ElementsBuffer.hpp"

using namespace std;

namespace GL
{
    ElementsBuffer::ElementsBuffer()
    {
        glGenBuffers(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[VertexBuffer] Out of memory");
        }
    }

    ElementsBuffer::~ElementsBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }

    ElementsBuffer::ElementsBuffer(const ElementsBuffer& _buffer)
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
                throw overflow_error("[Buffer] Out of memory");
            }
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
        }

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    }

    ElementsBuffer& ElementsBuffer::operator=(const ElementsBuffer& _buffer)
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
                    throw overflow_error("[Buffer] Out of memory");
                }
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
            }

            glBindBuffer(GL_COPY_READ_BUFFER, 0);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }
        return *this;
    }
}

#include "GL/VertexBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{

    VertexBuffer::VertexBuffer() :
        IGLObject()
    {
        glGenBuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        if(m_id == 0)
        {
            throw overflow_error("[VertexBuffer] Out of memory");
        }
    }

    VertexBuffer::~VertexBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
    }

    VertexBuffer::VertexBuffer(const VertexBuffer& _buffer) noexcept :
        IGLObject(_buffer)
    {
        glGenBuffers(1, &m_id);

        glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

        GLint size = 0;
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
        if (size != 0)
        {
            glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
            glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
        }

        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        assert(glGetError() == GL_NO_ERROR);
    }

    VertexBuffer& VertexBuffer::operator=(const VertexBuffer& _buffer) noexcept
    {
        if(this != &_buffer)
        {
            IGLObject::operator=(_buffer);

            glBindBuffer(GL_COPY_READ_BUFFER, _buffer.getId());
            glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

            GLint size = 0;
            glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
            if (size != 0)
            {
                glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
            }

            glBindBuffer(GL_COPY_READ_BUFFER, 0);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
            assert(glGetError() == GL_NO_ERROR);
        }
        return *this;
    }
}

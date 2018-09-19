#include "GL/ElementsBuffer.hpp"

#include <assert.h>
#include <stdexcept>

using namespace std;

namespace GL
{
    GLint ElementsBuffer::s_maxIndices;
    bool ElementsBuffer::s_first = false;

    ElementsBuffer::ElementsBuffer() :
        IGLObject()
    {
        if (!s_first)
        {
            s_first = true;
            glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &s_maxIndices);
        }
        glGenBuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        if(m_id == 0)
        {
            throw overflow_error("[ElementsBuffer] Out of memory");
        }
    }

    ElementsBuffer::~ElementsBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
    }

    ElementsBuffer::ElementsBuffer(const ElementsBuffer& _buffer) :
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

    ElementsBuffer& ElementsBuffer::operator=(const ElementsBuffer& _buffer)
    {
        if(this != &_buffer)
        {
            glDeleteBuffers(1, &m_id);
            IGLObject::operator=(_buffer);
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
        return *this;
    }
}

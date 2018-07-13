#include "GL/Buffer.hpp"

using namespace std;

namespace GL
{
    Buffer::Buffer(BUFFER_TYPE type) noexcept :
        m_type(type)
    {
        switch(m_type)
        {
        case BUFFER_TYPE::VAO:
            glGenVertexArrays(1, &m_id);
            break;
        case BUFFER_TYPE::VBO:
        case BUFFER_TYPE::EBO:
            glGenBuffers(1, &m_id);
            break;
        }
    }

    Buffer::~Buffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }

    Buffer::Buffer(const Buffer& _buffer) :
        m_type(_buffer.getType())
    {
        switch(m_type)
        {
        case BUFFER_TYPE::VAO:
            throw invalid_argument("[Buffer] can't copying VAO");
            break;
        case BUFFER_TYPE::VBO:
        case BUFFER_TYPE::EBO:
            glGenBuffers(1, &m_id);
            break;
        }

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
    }

    Buffer& Buffer::operator=(const Buffer& _buffer)
    {
        if(this != &_buffer)
        {
            glDeleteBuffers(1, &m_id);
            m_type = _buffer.getType();
            switch(m_type)
            {
            case BUFFER_TYPE::VAO:
                throw invalid_argument("[Buffer] can't copying VAO");
                break;
            case BUFFER_TYPE::VBO:
            case BUFFER_TYPE::EBO:
                glGenBuffers(1, &m_id);
                break;
            }

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
        }
        return *this;
    }

    void Buffer::bind() const noexcept
    {
        switch(m_type)
        {
        case VAO:
            glBindVertexArray(m_id);
            break;
        case VBO:
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
            break;
        case EBO:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
            break;
        }
    }

    void Buffer::unbind() const noexcept
    {
        switch(m_type)
        {
        case VAO:
            glBindVertexArray(0);
            break;
        case VBO:
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            break;
        case EBO:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            break;
        }
    }
}

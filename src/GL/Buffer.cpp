#include "GL/Buffer.hpp"

#include <iostream>
#include <stdexcept>

#define BUFFER_OFFSET(i) ((GLfloat*)nullptr + (i))

using namespace std;

namespace GL
{
    Buffer::Buffer(BUFFER_TYPE type) noexcept :
        m_type(type)
    {
        switch(m_type)
        {
        case VAO:
            glGenVertexArrays(1, &m_id);
            break;
        case VBO:
        case EBO:
            glGenBuffers(1, &m_id);
            break;
        case FBO:
            glGenFramebuffers(1, &m_id);
            break;
        case RBO:
            glGenRenderbuffers(1, &m_id);
            break;
        }
    }

    Buffer::~Buffer() noexcept
    {
        switch(m_type)
        {
        case VAO:
        case VBO:
        case EBO:
            glDeleteBuffers(1, &m_id);
            break;
        case FBO:
            glDeleteFramebuffers(1, &m_id);
            break;
        case RBO:
            glDeleteRenderbuffers(1, &m_id);
            break;
        }
    }

    Buffer::Buffer(const Buffer& _buffer) :
        m_type(_buffer.getType())
    {
        switch(m_type)
        {
        case BUFFER_TYPE::VAO:
            throw invalid_argument("[Buffer] can't copying VAO");
            break;
        case VBO:
        case EBO:
            glGenBuffers(1, &m_id);
            break;
        case FBO:
        case RBO:
            std::cerr << "TODO";
            break;
        }

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

    Buffer& Buffer::operator=(const Buffer& _buffer)
    {
        if(this != &_buffer)
        {
            glDeleteBuffers(1, &m_id);
            m_type = _buffer.getType();
            switch(m_type)
            {
            case VAO:
                throw invalid_argument("[Buffer] can't copying VAO");
                break;
            case VBO:
            case EBO:
                glGenBuffers(1, &m_id);
                break;
            case FBO:
            case RBO:
                std::cerr << "TODO";
                break;
            }

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

    void Buffer::setLocation(GLuint _location) const
    {
        switch(m_type)
        {
        case VAO:
        case EBO:
        case FBO:
        case RBO:
            throw bad_function_call();
            break;
        case VBO:
            glEnableVertexAttribArray(_location);
            break;
        }
    }

    void Buffer::setAttrib(GLuint _location, GLint _size, GLenum _type, GLboolean _normalize, GLsizei _stride, GLint _offset) const
    {
        switch(m_type)
        {
        case VAO:
        case EBO:
        case FBO:
        case RBO:
            throw bad_function_call();
            break;
        case VBO:
            glVertexAttribPointer(_location, _size, _type, _normalize, _stride, BUFFER_OFFSET(_offset));
            break;
        }
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
        case FBO:
            glBindFramebuffer(GL_FRAMEBUFFER, m_id);
            break;
        case RBO:
            glBindRenderbuffer(GL_RENDERBUFFER, m_id);
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
        case FBO:
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            break;
        case RBO:
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            break;
        }
    }
}

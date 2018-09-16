#pragma once

#include <GL/glew.h>

namespace GL 
{

class IBuffer
{

protected:

    IBuffer();
    virtual ~IBuffer() noexcept;
    IBuffer(const IBuffer&);
    IBuffer(IBuffer&&);
    IBuffer& operator=(const IBuffer&);
    IBuffer& operator=(IBuffer&&);

    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;

    inline GLuint getId() const noexcept;

protected:

    GLuint m_id {0};

};

inline GLuint IBuffer::getId() const noexcept
{
    return m_id;
}

}


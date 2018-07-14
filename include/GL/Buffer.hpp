#pragma once

#include <GL/glew.h>

namespace GL 
{

enum BUFFER_TYPE
{
    VAO,
    VBO,
    EBO
};

class Buffer
{

public:

    Buffer(BUFFER_TYPE) noexcept;
    ~Buffer() noexcept;
    Buffer(const Buffer&);
    Buffer& operator=(const Buffer&);

    void bind() const noexcept;
    void unbind() const noexcept;

    inline BUFFER_TYPE getType() const noexcept;
    inline GLuint getId() const noexcept;

private:

    GLuint m_id {0};
    BUFFER_TYPE m_type {VBO};

};

BUFFER_TYPE Buffer::getType() const noexcept
{
    return m_type;
}

GLuint Buffer::getId() const noexcept
{
    return m_id;
}

}


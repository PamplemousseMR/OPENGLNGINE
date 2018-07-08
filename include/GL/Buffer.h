#pragma once

#include <GL/glew.h>

#include <iostream>

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

    Buffer(BUFFER_TYPE);
    ~Buffer();
    Buffer(const Buffer&) throw(...);
    Buffer& operator=(const Buffer&) throw(...);

    void bind() const;
    void unbind() const;

    BUFFER_TYPE getType() const;
    GLuint getId() const;

private:

    GLuint m_id;
    BUFFER_TYPE m_type;

};

}


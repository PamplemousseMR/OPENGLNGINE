#pragma once

#include <GL/glew.h>

#include <functional>
#include <vector>

namespace GL 
{

class Buffer
{

public:

    enum BUFFER_TYPE
    {
        VBO,
        VAO,
        EBO,
        FBO,
        RBO,
    };

public:

    Buffer(BUFFER_TYPE);
    ~Buffer() noexcept;
    Buffer(const Buffer&);
    Buffer(Buffer&&) = delete;
    Buffer& operator=(const Buffer&);
    Buffer& operator=(Buffer&&) = delete;

    template<typename T>
    void setData(const std::vector<T>&) const;
    void setLocation(GLuint) const;
    void setAttrib(GLuint, GLint, GLenum, GLboolean, GLsizei, GLint) const;

    void bind() const noexcept;
    void unbind() const noexcept;

    inline BUFFER_TYPE getType() const noexcept;
    inline GLuint getId() const noexcept;

private:

    GLuint m_id {0};
    BUFFER_TYPE m_type {VBO};

};

inline Buffer::BUFFER_TYPE Buffer::getType() const noexcept
{
    return m_type;
}

inline GLuint Buffer::getId() const noexcept
{
    return m_id;
}

template<typename T>
void Buffer::setData(const std::vector<T>& _arr) const
{
    GLenum target;
    switch(m_type)
    {
    case FBO:
    case VAO:
    case RBO:
        throw bad_function_call();
        break;
    case VBO:
        target = GL_ARRAY_BUFFER;
        break;
    case EBO:
        target = GL_ELEMENT_ARRAY_BUFFER;
        break;
    }
    glBufferData(target, _arr.size() * sizeof(T), &_arr[0], GL_STATIC_DRAW);
}

}


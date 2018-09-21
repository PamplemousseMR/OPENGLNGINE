#pragma once

#include <GL/glew.h>

namespace GL 
{

class IGLObject
{

public:

    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;

    inline GLuint getId() const noexcept;

protected:

    IGLObject();
    virtual ~IGLObject() noexcept;
    IGLObject(const IGLObject&);
    IGLObject(IGLObject&&) = delete;
    IGLObject& operator=(const IGLObject&);
    IGLObject& operator=(IGLObject&&) = delete;

protected:

    GLuint m_id;

};

inline GLuint IGLObject::getId() const noexcept
{
    return m_id;
}

}


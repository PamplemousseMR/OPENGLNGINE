#pragma once

#include <GL/glew.h>

namespace GL 
{

class IObject
{

public:

    inline GLuint getId() const noexcept;

protected:

    IObject();
    virtual ~IObject() noexcept;
    IObject(const IObject&);
    IObject(IObject&&) = delete;
    IObject& operator=(const IObject&);
    IObject& operator=(IObject&&) = delete;

protected:

    GLuint m_id;

};

inline GLuint IObject::getId() const noexcept
{
    return m_id;
}

}


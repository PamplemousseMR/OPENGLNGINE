#pragma once

#include <GL/glew.h>

#include "GL/IObject.hpp"

namespace GL
{

class IBindable : public IObject
{

public:

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

protected:

    IBindable();
    virtual ~IBindable();
    IBindable(const IBindable&);
    IBindable(IBindable&&) = delete;
    IBindable& operator=(const IBindable&);
    IBindable& operator=(IBindable&&) = delete;

};

}


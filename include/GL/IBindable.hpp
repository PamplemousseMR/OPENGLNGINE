#pragma once

#include <GL/glew.h>

#include "GL/IObject.hpp"

namespace GL
{

class IBindable : public IObject
{

public:

    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;

protected:

    IBindable();
    virtual ~IBindable() noexcept;
    IBindable(const IBindable&);
    IBindable(IBindable&&) = delete;
    IBindable& operator=(const IBindable&);
    IBindable& operator=(IBindable&&) = delete;

};

}


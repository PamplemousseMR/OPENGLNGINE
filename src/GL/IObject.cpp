#include "GL/IObject.hpp"

namespace GL
{
    IObject::IObject()
    {
    }

    IObject::~IObject()
    {
    }

    IObject::IObject(const IObject&)
    {
    }

    IObject& IObject::operator=(const IObject&)
    {
        return *this;
    }
}

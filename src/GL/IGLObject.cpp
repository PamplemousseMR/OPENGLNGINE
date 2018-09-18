#include "GL/IGLObject.hpp"

namespace GL
{
    IGLObject::IGLObject()
    {
    }

    IGLObject::~IGLObject() noexcept
    {
    }

    IGLObject::IGLObject(const IGLObject&)
    {
    }

    IGLObject& IGLObject::operator=(const IGLObject&)
    {
        return *this;
    }
}

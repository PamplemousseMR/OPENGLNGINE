#include "GL/IBindable.hpp"

namespace GL
{
    IBindable::IBindable() :
        IObject()
    {
    }

    IBindable::~IBindable()
    {
    }

    IBindable::IBindable(const IBindable& _iBindable) :
        IObject(_iBindable)
    {
    }

    IBindable& IBindable::operator=(const IBindable& _iBindable)
    {
        IObject::operator =(_iBindable);
        return *this;
    }
}

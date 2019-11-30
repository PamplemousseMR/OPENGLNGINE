#pragma once

#include "Scene/IMovable.hpp"

#include <string>

namespace Scene
{

class IMovableObject :
        public IMovable
{

public:

    static const std::string s_FACTORY_TYPE_NAME;

    virtual ~IMovableObject();

protected:

    IMovableObject();
    IMovableObject(const std::string&);

private:

    IMovableObject(const IMovableObject&) = delete;
    IMovableObject(IMovableObject&&) = delete;
    IMovableObject& operator=(const IMovableObject&) = delete;
    IMovableObject& operator=(IMovableObject&&) = delete;

};

}

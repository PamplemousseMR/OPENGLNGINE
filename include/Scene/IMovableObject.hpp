#pragma once

#include "Scene/IMovable.hpp"

#include <string>

namespace Scene
{

class IMovableObject :
        public IMovable
{

public:

    friend class SceneManager;

    static const std::string s_FACTORY_TYPE_NAME;

protected:

    IMovableObject();
    IMovableObject(const std::string&);
    virtual ~IMovableObject();

};

}

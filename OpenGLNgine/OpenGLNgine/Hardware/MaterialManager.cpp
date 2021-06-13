#include "OpenGLNgine/Hardware/MaterialManager.hpp"

namespace Hardware
{

MaterialPtr MaterialManager::create(const std::string& _name)
{
    MaterialPtr ptr(new Material(this, _name));
    this->add(ptr);
    return ptr;
}

MaterialManager::MaterialManager():
    ::Core::IManager<Material>()
{
}

MaterialManager::~MaterialManager()
{
}

}

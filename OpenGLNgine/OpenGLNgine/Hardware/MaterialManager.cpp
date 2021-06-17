#include "OpenGLNgine/Hardware/MaterialManager.hpp"

namespace Hardware
{

MaterialPtr MaterialManager::create(const std::string& _name)
{
    MaterialPtr ptr(new Material(this, _name));
    this->add(ptr);
    return ptr;
}

MaterialPtr MaterialManager::getByName(const std::string& _name) const
{
    return std::dynamic_pointer_cast< Material >(this->get(_name));
}

MaterialManager::MaterialManager(const ::Render::RenderWindow* const _renderWindow) :
    ::Core::IHardwareManager(_renderWindow)
{
}

MaterialManager::~MaterialManager()
{
}

}

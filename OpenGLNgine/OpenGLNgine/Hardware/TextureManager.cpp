#include "OpenGLNgine/Hardware/TextureManager.hpp"

namespace Hardware
{

TexturePtr TextureManager::create(const std::string& _name, TEXTURE_TYPE _type)
{
    TexturePtr ptr(new Texture(this, _name, _type));
    this->add(ptr);
    return ptr;
}

TexturePtr TextureManager::getByName(const std::string& _name) const
{
    return std::dynamic_pointer_cast< Texture >(this->get(_name));
}

TextureManager::TextureManager():
    Core::IHardwareManager()
{
}

TextureManager::~TextureManager()
{
}

}

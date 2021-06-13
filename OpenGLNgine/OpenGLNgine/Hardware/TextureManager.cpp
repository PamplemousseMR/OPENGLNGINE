#include "OpenGLNgine/Hardware/TextureManager.hpp"

namespace Hardware
{

TexturePtr TextureManager::create(const std::string& _name, TEXTURE_TYPE _type)
{
    TexturePtr ptr(new Texture(this, _name, _type));
    this->add(ptr);
    return ptr;
}

TextureManager::TextureManager():
    Core::IManager<Texture>()
{
}

TextureManager::~TextureManager()
{
}

}

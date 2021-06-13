#include "OpenGLNgine/Hardware/TextureManager.hpp"

namespace Hardware
{

TextureManager* TextureManager::s_instance = nullptr;

TextureManager& TextureManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

TexturePtr TextureManager::create(const std::string& _name, TEXTURE_TYPE _type)
{
    TexturePtr ptr = std::make_shared< Texture >(this, _name, _type);
    this->add(ptr);
    return ptr;
}

TextureManager::Initializer::Initializer()
{
    TextureManager::s_instance = new TextureManager();
}

TextureManager::Initializer::~Initializer()
{
    delete TextureManager::s_instance;
    TextureManager::s_instance = nullptr;
}

TextureManager::TextureManager():
    Core::IManager<Texture>()
{
}

TextureManager::~TextureManager()
{
}

}

#include "OpenGLNgine/Hardware/TextureManager.hpp"

namespace Hardware
{

TextureManager* TextureManager::s_instance = nullptr;

TextureManager& TextureManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

TexturePtr TextureManager::create(const std::string& _name)
{
    TexturePtr ptr = std::make_shared< Texture >(this, _name);
    this->add(ptr);
    return ptr;
}

TexturePtr TextureManager::getByName(const std::string& _name)
{
    return this->get(_name);
}

void TextureManager::destroy(const TexturePtr& _texture)
{
    this->remove(_texture);
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

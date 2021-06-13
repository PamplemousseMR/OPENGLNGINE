#include "OpenGLNgine/Hardware/MaterialManager.hpp"

namespace Hardware
{

MaterialManager* MaterialManager::s_instance = nullptr;

MaterialManager& MaterialManager::getInstance()
{
    const static Initializer s_INITIALIZER;
    return *s_instance;
}

MaterialPtr MaterialManager::create(const std::string& _name)
{
    MaterialPtr ptr = std::make_shared< Material >(this, _name);
    this->add(ptr);
    return ptr;
}

MaterialManager::Initializer::Initializer()
{
    MaterialManager::s_instance = new MaterialManager();
}

MaterialManager::Initializer::~Initializer()
{
    delete MaterialManager::s_instance;
    MaterialManager::s_instance = nullptr;
}

MaterialManager::MaterialManager():
    ::Core::IManager<Material>()
{
}

MaterialManager::~MaterialManager()
{
}

}

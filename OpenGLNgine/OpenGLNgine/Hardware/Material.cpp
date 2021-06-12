#include "OpenGLNgine/Hardware/Material.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <algorithm>

namespace Hardware
{

Material::Material(MaterialManager* const _manager, const std::string& _name):
    ::Core::IResource(_name),
    m_manager(_manager)
{
    this->createPass();
}

Material::~Material()
{
    this->destroyAllPasses();
}

Pass* Material::createPass()
{
    Pass* const ptr = new Pass();
    m_passes.push_back(ptr);
    return ptr;
}

void Material::destroyAllPasses()
{
    PassList::const_iterator itBeg = m_passes.begin();
    const PassList::const_iterator itEnd = m_passes.end();
    for(; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_passes.clear();
}

}

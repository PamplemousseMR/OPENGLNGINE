#include "OpenGLNgine/Hardware/Material.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Hardware
{

Material::Material(MaterialManager* const _manager, const std::string& _name):
    Core::IResource(_name),
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
    Pass* ptr = new Pass();
    m_passes.push_back(ptr);
    return ptr;
}

void Material::destroyPass(Pass* const _pass)
{
    GLNGINE_ASSERT_IF(!_pass, "The pass mustn't be null");

    PassList::const_iterator it = std::find(m_passes.begin(), m_passes.end(), _pass);
    if(it == m_passes.end())
    {
        GLNGINE_EXCEPTION("The pass doesn't exists");
    }
    m_passes.erase(it);
    delete _pass;
}

void Material::destroyAllPasses()
{
    PassList::const_iterator itBeg, itEnd;
    itEnd = m_passes.end();
    for(itBeg=m_passes.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_passes.clear();
}

}

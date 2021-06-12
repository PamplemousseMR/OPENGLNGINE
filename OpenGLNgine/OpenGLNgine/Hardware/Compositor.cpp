#include "OpenGLNgine/Hardware/Compositor.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Hardware
{

Compositor::Compositor(CompositorManager* const _manager, const std::string& _name):
    ::Core::IResource(_name),
    m_manager(_manager)
{
}

Compositor::~Compositor()
{
    this->destroyAllCompositorTargetPasses();
}

CompositorTargetPass* Compositor::createCompositorTargetPass()
{
    CompositorTargetPass* ptr = new CompositorTargetPass();
    m_compositorTargetPasses.push_back(ptr);
    return ptr;
}

void Compositor::destroyCompositorTargetPass(CompositorTargetPass* const _pass)
{
    GLNGINE_ASSERT_IF(!_pass, "The pass mustn't be null");

    CompositorTargetPassList::const_iterator it = std::find(m_compositorTargetPasses.begin(), m_compositorTargetPasses.end(), _pass);
    if(it == m_compositorTargetPasses.end())
    {
        GLNGINE_EXCEPTION("The pass doesn't exists");
    }
    m_compositorTargetPasses.erase(it);
    delete _pass;
}

void Compositor::destroyAllCompositorTargetPasses()
{
    CompositorTargetPassList::const_iterator itBeg, itEnd;
    itEnd = m_compositorTargetPasses.end();
    for(itBeg=m_compositorTargetPasses.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_compositorTargetPasses.clear();
}

}

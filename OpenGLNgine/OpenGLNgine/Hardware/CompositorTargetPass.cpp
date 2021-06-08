#include "OpenGLNgine/Hardware/CompositorTargetPass.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Hardware
{

CompositorTargetPass::CompositorTargetPass()
{
}

CompositorTargetPass::~CompositorTargetPass()
{
}

CompositorPassClear* CompositorTargetPass::createCompositorPassClear()
{
    CompositorPassClear* const ptr = new CompositorPassClear();
    m_compositorPasses.push_back(ptr);
    return ptr;
}

void CompositorTargetPass::destroyCompositorPass(CompositorPass* const _pass)
{
    GLNGINE_ASSERT_IF(!_pass, "The pass mustn't be null");

    CompositorPassList::const_iterator it = std::find(m_compositorPasses.begin(), m_compositorPasses.end(), _pass);
    if(it == m_compositorPasses.end())
    {
        GLNGINE_EXCEPTION("The pass doesn't exists");
    }
    m_compositorPasses.erase(it);
    delete _pass;
}

void CompositorTargetPass::destroyAllCompositorPasses()
{
    CompositorPassList::const_iterator itBeg, itEnd;
    itEnd = m_compositorPasses.end();
    for(itBeg=m_compositorPasses.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_compositorPasses.clear();
}

}

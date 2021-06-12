#include "OpenGLNgine/Hardware/CompositorPassClear.hpp"
#include "OpenGLNgine/Hardware/CompositorTargetPass.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace Hardware
{

::GL::FRAMBUFFER_MASK CompositorTargetPass::getType(COMPOSITORTARGETPASS_MASK _type)
{
    switch(_type)
    {
    case CM_COLOR:
        return ::GL::FM_COLOR;
    case CM_DEPTH:
        return ::GL::FM_DEPTH;
    case CM_STENCIL:
        return ::GL::FM_STENCIL;
    case CM_COLOR_DEPTH:
        return ::GL::FM_COLOR_DEPTH;
    case CM_COLOR_STENCIL:
        return ::GL::FM_COLOR_STENCIL;
    case CM_DEPTH_STENCIL:
        return ::GL::FM_DEPTH_STENCIL;
    case CM_ALL:
        return ::GL::FM_ALL;
    default:
        GLNGINE_EXCEPTION("Unhandle mask type");
    }
}

::GL::FRAMBUFFER_FILTER CompositorTargetPass::getType(COMPOSITORTARGETPASS_FILTER _type)
{
    switch(_type)
    {
    case CF_LINEAR:
        return ::GL::FF_LINEAR;
    case CF_NEAREST:
        return ::GL::FF_NEAREST;
    default:
        GLNGINE_EXCEPTION("Unhandle filter type");
    }
}

CompositorTargetPass::CompositorTargetPass()
{
}

CompositorTargetPass::~CompositorTargetPass()
{
}

CompositorPass* CompositorTargetPass::createCompositorPass(COMPOSITORPASS_TYPE _type)
{
    CompositorPass* ptr = nullptr;
    switch (_type) {
    case CT_CLEAR:
        ptr = new CompositorPassClear();
        break;
    case CT_SCENE:
        ptr = new CompositorPass(_type);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle compositor pass type");
    }
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

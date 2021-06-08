#include "OpenGLNgine/Hardware/CompositorPassClear.hpp"

namespace Hardware
{

::GL::DRAWCALL_CLEAR CompositorPassClear::getType(COMPOSITORPASS_CLEAR _type)
{
    switch(_type)
    {
    case CC_COLOR:
        return ::GL::DC_COLOR;
    case CC_DEPTH:
        return ::GL::DC_DEPTH;
    case CC_STENCIL:
        return ::GL::DC_STENCIL;
    case CC_COLOR_DEPTH:
        return ::GL::DC_COLOR_DEPTH;
    case CC_COLOR_STENCIL:
        return ::GL::DC_COLOR_STENCIL;
    case CC_DEPTH_STENCIL:
        return ::GL::DC_DEPTH_STENCIL;
    case CC_ALL:
        return ::GL::DC_ALL;
    default:
        GLNGINE_EXCEPTION("Unhandle clear type");
    }
}

CompositorPassClear::CompositorPassClear() :
    CompositorPass(CT_CLEAR)
{
}

CompositorPassClear::~CompositorPassClear()
{
}

}

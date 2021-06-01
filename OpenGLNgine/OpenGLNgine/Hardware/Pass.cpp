#include "OpenGLNgine/Hardware/Pass.hpp"

namespace Hardware
{

::GL::PIXELOPERATION_DEPTH Pass::getType(PASS_DEPTH _type)
{
    switch(_type)
    {
    case PD_NEVER:
        return ::GL::PD_NEVER;
    case PD_LESS:
        return ::GL::PD_LESS;
    case PD_EQUAL:
        return ::GL::PD_EQUAL;
    case PD_LEQUAL:
        return ::GL::PD_LEQUAL;
    case PD_GREATER:
        return ::GL::PD_GREATER;
    case PD_NOTEQUAL:
        return ::GL::PD_NOTEQUAL;
    case PD_GEQUAL:
        return ::GL::PD_GEQUAL;
    case PD_ALWAYS:
        return ::GL::PD_ALWAYS;
    default:
        GLNGINE_EXCEPTION("Unhandle depth function");
    }
}

::GL::PIXELOPERATION_BLEND Pass::getType(PASS_BLEND _type)
{
    switch(_type)
    {
    case PB_ZERO:
        return ::GL::PB_ZERO;
    case PB_ONE:
        return ::GL::PB_ONE;
    case PB_SRC_COLOR:
        return ::GL::PB_SRC_COLOR;
    case PB_ONE_MINUS_SRC_COLOR:
        return ::GL::PB_ONE_MINUS_SRC_COLOR;
    case PB_DST_COLOR:
        return ::GL::PB_DST_COLOR;
    case PB_ONE_MINUS_DST_COLOR:
        return ::GL::PB_ONE_MINUS_DST_COLOR;
    case PB_SRC_ALPHA:
        return ::GL::PB_SRC_ALPHA;
    case PB_ONE_MINUS_SRC_ALPHA:
        return ::GL::PB_ONE_MINUS_SRC_ALPHA;
    case PB_DST_ALPHA:
        return ::GL::PB_DST_ALPHA;
    case PB_ONE_MINUS_DST_ALPHA:
        return ::GL::PB_ONE_MINUS_DST_ALPHA;
    case PB_CONSTANT_COLOR:
        return ::GL::PB_CONSTANT_COLOR;
    case PB_ONE_MINUS_CONSTANT_COLOR:
        return ::GL::PB_ONE_MINUS_CONSTANT_COLOR;
    case PB_CONSTANT_ALPHA:
        return ::GL::PB_CONSTANT_ALPHA;
    case PB_ONE_MINUS_CONSTANT_ALPHA:
        return ::GL::PB_ONE_MINUS_CONSTANT_ALPHA;
    case PB_SRC_ALPHA_SATURATE:
        return ::GL::PB_SRC_ALPHA_SATURATE;
    case PB_SRC1_COLOR:
        return ::GL::PB_SRC1_COLOR;
    case PB_ONE_MINUS_SRC1_COLOR:
        return ::GL::PB_ONE_MINUS_SRC1_COLOR;
    case PB_SRC1_ALPHA:
        return ::GL::PB_SRC1_ALPHA;
    case PB_ONE_MINUS_SRC1_ALPHA:
        return ::GL::PB_ONE_MINUS_SRC1_ALPHA;
    default:
        GLNGINE_EXCEPTION("Unhandle blend type");
    }
}

::GL::RASTERIZER_CULLFACE Pass::getType(PASS_CULLING _type)
{
    switch(_type)
    {
    case PC_BACK:
        return ::GL::RC_BACK;
    case PC_FRONT:
        return ::GL::RC_FRONT;
    case PC_FRONT_AND_BACK:
        return ::GL::RC_BACK_AND_FRONT;
    default:
        GLNGINE_EXCEPTION("Unhandle culling mode");
    }
}

Pass::Pass()
{
}

Pass::~Pass()
{
    this->destroyAllTextureUnitStates();
}

TextureUnitState* Pass::createTextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic)
{
    TextureUnitStateList::const_iterator it, itEnd;
    itEnd = m_textureUnitStates.end();
    for(it=m_textureUnitStates.begin() ; it!=itEnd ; ++it)
    {
        if((*it)->m_semantic == _semantic)
        {
            delete *it;
            m_textureUnitStates.erase(it);
            break;
        }
    }

    m_textureUnitStates.push_back(new TextureUnitState(_semantic));
    return m_textureUnitStates.back();
}

TextureUnitState* Pass::findTextureUnitStateBySemantic(TEXTUREUNITSTATE_SEMANTIC _semantic) const
{
    TextureUnitStateList::const_iterator it, itEnd;
    itEnd = m_textureUnitStates.end();
    for(it=m_textureUnitStates.begin() ; it!=itEnd ; ++it)
    {
        if((*it)->m_semantic == _semantic)
        {
            return *it;
        }
    }
    return nullptr;
}

void Pass::destroyAllTextureUnitStates()
{
    TextureUnitStateList::const_iterator itBeg, itEnd;
    itEnd = m_textureUnitStates.end();
    for(itBeg=m_textureUnitStates.begin() ; itBeg!=itEnd ; ++itBeg)
    {
        delete *itBeg;
    }
    m_textureUnitStates.clear();
}

}

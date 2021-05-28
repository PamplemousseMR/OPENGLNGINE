#include "OpenGLNgine/Hardware/Pass.hpp"

namespace Hardware
{

::GL::PIXELOPERATION_DEPTH Pass::getType(MATERIAL_DEPTH _type)
{
    switch(_type)
    {
    case MD_NEVER:
        return ::GL::PD_NEVER;
    case MD_LESS:
        return ::GL::PD_LESS;
    case MD_EQUAL:
        return ::GL::PD_EQUAL;
    case MD_LEQUAL:
        return ::GL::PD_LEQUAL;
    case MD_GREATER:
        return ::GL::PD_GREATER;
    case MD_NOTEQUAL:
        return ::GL::PD_NOTEQUAL;
    case MD_GEQUAL:
        return ::GL::PD_GEQUAL;
    case MD_ALWAYS:
        return ::GL::PD_ALWAYS;
    default:
        GLNGINE_EXCEPTION("Unhandle depth function");
    }
}

::GL::PIXELOPERATION_BLEND Pass::getType(MATERIAL_BLEND _type)
{
    switch(_type)
    {
    case MB_ZERO:
        return ::GL::PB_ZERO;
    case MB_ONE:
        return ::GL::PB_ONE;
    case MB_SRC_COLOR:
        return ::GL::PB_SRC_COLOR;
    case MB_ONE_MINUS_SRC_COLOR:
        return ::GL::PB_ONE_MINUS_SRC_COLOR;
    case MB_DST_COLOR:
        return ::GL::PB_DST_COLOR;
    case MB_ONE_MINUS_DST_COLOR:
        return ::GL::PB_ONE_MINUS_DST_COLOR;
    case MB_SRC_ALPHA:
        return ::GL::PB_SRC_ALPHA;
    case MB_ONE_MINUS_SRC_ALPHA:
        return ::GL::PB_ONE_MINUS_SRC_ALPHA;
    case MB_DST_ALPHA:
        return ::GL::PB_DST_ALPHA;
    case MB_ONE_MINUS_DST_ALPHA:
        return ::GL::PB_ONE_MINUS_DST_ALPHA;
    case MB_CONSTANT_COLOR:
        return ::GL::PB_CONSTANT_COLOR;
    case MB_ONE_MINUS_CONSTANT_COLOR:
        return ::GL::PB_ONE_MINUS_CONSTANT_COLOR;
    case MB_CONSTANT_ALPHA:
        return ::GL::PB_CONSTANT_ALPHA;
    case MB_ONE_MINUS_CONSTANT_ALPHA:
        return ::GL::PB_ONE_MINUS_CONSTANT_ALPHA;
    case MB_SRC_ALPHA_SATURATE:
        return ::GL::PB_SRC_ALPHA_SATURATE;
    case MB_SRC1_COLOR:
        return ::GL::PB_SRC1_COLOR;
    case MB_ONE_MINUS_SRC1_COLOR:
        return ::GL::PB_ONE_MINUS_SRC1_COLOR;
    case MB_SRC1_ALPHA:
        return ::GL::PB_SRC1_ALPHA;
    case MB_ONE_MINUS_SRC1_ALPHA:
        return ::GL::PB_ONE_MINUS_SRC1_ALPHA;
    default:
        GLNGINE_EXCEPTION("Unhandle blend type");
    }
}

void Pass::lock()
{
    if(m_program)
    {
        m_program->lock();
    }
}

void Pass::unlock()
{
    if(m_program)
    {
        m_program->unlock();
    }}

Pass::Pass()
{
}

Pass::~Pass()
{
    this->destroyAllTextureUnitStates();
}

TextureUnitState* Pass::createTextureUnitState()
{
    TextureUnitState* ptr = new TextureUnitState();
    m_textureUnitStates.push_back(ptr);
    return ptr;
}

void Pass::destroyTextureUnitState(TextureUnitState* const _textureUnitState)
{
    GLNGINE_ASSERT_IF(!_textureUnitState, "The texture unit state mustn't be null");

    TextureUnitStateList::const_iterator it = std::find(m_textureUnitStates.begin(), m_textureUnitStates.end(), _textureUnitState);
    if(it == m_textureUnitStates.end())
    {
        GLNGINE_EXCEPTION("The texture unit state doesn't exists");
    }
    m_textureUnitStates.erase(it);
    delete _textureUnitState;
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

#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

namespace Hardware
{

void TextureUnitState::lock()
{
    if(m_texture)
    {
        m_texture->lock();
    }
}

void TextureUnitState::unlock()
{
    if(m_texture)
    {
        m_texture->unlock();
    }
}

TextureUnitState::TextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic):
    m_semantic(_semantic)
{
}

TextureUnitState::~TextureUnitState()
{
}

}

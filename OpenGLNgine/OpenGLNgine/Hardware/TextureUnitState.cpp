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

TextureUnitState::TextureUnitState()
{
}

TextureUnitState::~TextureUnitState()
{
}

}

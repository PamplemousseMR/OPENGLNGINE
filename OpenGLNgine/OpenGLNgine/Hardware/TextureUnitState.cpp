#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

namespace Hardware
{

void TextureUnitState::setTexture(TexturePtr _texture)
{
    GLNGINE_ASSERT_IF(!_texture, "The texture mustn't be null");
    m_texture = _texture;
}

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

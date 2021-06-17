#include "OpenGLNgine/Hardware/TextureUnitState.hpp"

namespace Hardware
{

void TextureUnitState::setTexture(TexturePtr _texture)
{
    GLNGINE_ASSERT_IF(!_texture, "The texture shall not be null");
    m_texture = _texture;
}

TextureUnitState::TextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic) :
    m_semantic(_semantic)
{
}

TextureUnitState::~TextureUnitState()
{
}

}

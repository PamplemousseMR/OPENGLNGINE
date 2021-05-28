#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

namespace Hardware
{

class Pass;

class TextureUnitState
{

    friend Pass;

public:

    inline void setTexture(TexturePtr _texture);

    void lock();

    void unlock();

    inline TexturePtr getTexture() const;

    TEXTURE_FILTER minFilter { TF_NEAREST };

    TEXTURE_FILTER magFilter { TF_NEAREST };

private:

    TextureUnitState();

    ~TextureUnitState();

    TexturePtr m_texture { nullptr };

};

inline void TextureUnitState::setTexture(TexturePtr _texture)
{
    GLNGINE_ASSERT_IF(!_texture, "The texture mustn't be null");
    m_texture = _texture;
}

inline TexturePtr TextureUnitState::getTexture() const
{
    return m_texture;
}

}

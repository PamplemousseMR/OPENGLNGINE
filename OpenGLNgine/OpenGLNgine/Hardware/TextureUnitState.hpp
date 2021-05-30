#pragma once

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

namespace Hardware
{

class Pass;

enum TEXTUREUNITSTATE_SEMANTIC : unsigned
{
    TS_DIFFUSE = 0,
    TS_SPECULAR = 1,
    TS_AMBIENT = 2,
    TS_EMISSIVE = 3,
    TS_HEIGHT = 4,
    TS_NORMALS = 5,
    TS_SHININESS = 6,
    TS_OPACITY = 7,
    TS_DISPLACEMENT = 8,
    TS_LIGHTMAP = 9,
    TS_REFLECTION = 10,
    TS_NONE = 11
};

enum WRAP_MODE
{
    WM_REPEAT,
    WM_CLAMP,
    WM_BORDER,
    WM_MIRROR
};

class TextureUnitState
{

    friend Pass;

public:

    TextureUnitState(const TextureUnitState&) = delete;

    TextureUnitState(TextureUnitState&&) = delete;

    TextureUnitState& operator=(const TextureUnitState&) = delete;

    TextureUnitState& operator=(TextureUnitState&&) = delete;

    inline void setTexture(TexturePtr _texture);

    void lock();

    void unlock();

    inline TexturePtr getTexture() const;

    const TEXTUREUNITSTATE_SEMANTIC m_semantic;

    TEXTURE_FILTER minFilter { TF_NEAREST };

    TEXTURE_FILTER magFilter { TF_NEAREST };

    WRAP_MODE m_uWrap { WM_REPEAT };

    WRAP_MODE m_vWrap { WM_REPEAT };

private:

    TextureUnitState(TEXTUREUNITSTATE_SEMANTIC _semantic);

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

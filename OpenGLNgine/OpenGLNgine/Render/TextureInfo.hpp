#pragma once

#include <filesystem>

namespace Render
{

enum TEXTURE_TYPE
{
    TT_NONE,
    TT_DIFFUSE,
    TT_SPECULAR,
    TT_AMBIENT,
    TT_EMISSIVE,
    TT_HEIGHT,
    TT_NORMALS,
    TT_SHININESS,
    TT_OPACITY,
    TT_DISPLACEMENT,
    TT_LIGHTMAP,
    TT_REFLECTION
};

enum WRAP_MODE
{
    WM_REPEAT,
    WM_CLAMP,
    WM_BORDER,
    WM_MIRROR
};

class MaterialInfo;

class TextureInfo final
{

    friend MaterialInfo;

public:

    TextureInfo(const TextureInfo&) = delete;

    TextureInfo(TextureInfo&&) = delete;

    TextureInfo& operator=(const TextureInfo&) = delete;

    TextureInfo& operator=(TextureInfo&&) = delete;

    const TEXTURE_TYPE m_type;

    std::filesystem::path m_path { "" };

    WRAP_MODE m_uWrap { WM_REPEAT };

    WRAP_MODE m_vWrap { WM_REPEAT };

private:

    TextureInfo(TEXTURE_TYPE _type);

    ~TextureInfo();

};

}

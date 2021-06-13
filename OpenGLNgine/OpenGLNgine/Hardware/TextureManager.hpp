#pragma once

#include "OpenGLNgine/Core/IManager.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class TextureManager final : public Core::IManager< Texture >
{

    friend ::Render::RenderWindow;

public:

    TextureManager(const TextureManager&) = delete;

    TextureManager(TextureManager&&) = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager& operator=(TextureManager&&) = delete;

    TexturePtr create(const std::string& _name, TEXTURE_TYPE _type);

private:

    TextureManager();

    ~TextureManager();

};

}

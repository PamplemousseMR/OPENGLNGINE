#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class TextureManager final : public Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    TextureManager(const TextureManager&) = delete;

    TextureManager(TextureManager&&) = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager& operator=(TextureManager&&) = delete;

    TexturePtr create(const std::string& _name, TEXTURE_TYPE _type);

    TexturePtr getByName(const std::string& _name) const;

private:

    TextureManager(const ::Render::RenderWindow* const _renderWindow);

    ~TextureManager();

};

}

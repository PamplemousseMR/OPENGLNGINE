#pragma once

#include "OpenGLNgine/Core/IManager.hpp"
#include "OpenGLNgine/Hardware/Texture.hpp"

namespace Hardware
{

class TextureManager final : public Core::IManager< Texture >
{

public:

    static TextureManager& getInstance();

    TextureManager(const TextureManager&) = delete;

    TextureManager(TextureManager&&) = delete;

    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager& operator=(TextureManager&&) = delete;

    TexturePtr create(const std::string& _name);

    TexturePtr getByName(const std::string& _name);

    void destroy(const TexturePtr& _Texture);

private:

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static TextureManager* s_instance;

    TextureManager();

    ~TextureManager();

};

}

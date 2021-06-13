#pragma once

#include "OpenGLNgine/Core/IManager.hpp"

#include "OpenGLNgine/Hardware/Material.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class MaterialManager final : public ::Core::IManager< Material >
{

    friend ::Render::RenderWindow;

public:

    MaterialManager(const MaterialManager&) = delete;

    MaterialManager(MaterialManager&&) = delete;

    MaterialManager& operator=(const MaterialManager&) = delete;

    MaterialManager& operator=(MaterialManager&&) = delete;

    MaterialPtr create(const std::string& _name);

private:

    MaterialManager();

    ~MaterialManager();

};

}

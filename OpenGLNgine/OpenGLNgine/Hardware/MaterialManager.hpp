#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"

#include "OpenGLNgine/Hardware/Material.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class MaterialManager final : public ::Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    MaterialManager(const MaterialManager&) = delete;

    MaterialManager(MaterialManager&&) = delete;

    MaterialManager& operator=(const MaterialManager&) = delete;

    MaterialManager& operator=(MaterialManager&&) = delete;

    MaterialPtr create(const std::string& _name);

    MaterialPtr getByName(const std::string& _name) const;
private:

    MaterialManager(const ::Render::RenderWindow* const _renderWindow);

    ~MaterialManager();

};

}

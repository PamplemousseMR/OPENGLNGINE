#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"

#include "OpenGLNgine/Hardware/Compositor.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class CompositorManager final : public ::Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    CompositorManager(const CompositorManager&) = delete;

    CompositorManager(CompositorManager&&) = delete;

    CompositorManager& operator=(const CompositorManager&) = delete;

    CompositorManager& operator=(CompositorManager&&) = delete;

    CompositorPtr create(const std::string& _name);

private:

    CompositorManager();

    ~CompositorManager();

};

}

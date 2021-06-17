#pragma once

#include "OpenGLNgine/Core/IHardwareManager.hpp"

#include "OpenGLNgine/Hardware/RenderTarget.hpp"

namespace Render
{
    class RenderWindow;
}

namespace Hardware
{

class RenderTargetManager final : public ::Core::IHardwareManager
{

    friend ::Render::RenderWindow;

public:

    RenderTargetManager(const RenderTargetManager&) = delete;

    RenderTargetManager(RenderTargetManager&&) = delete;

    RenderTargetManager& operator=(const RenderTargetManager&) = delete;

    RenderTargetManager& operator=(RenderTargetManager&&) = delete;

    RenderTargetPtr create(const std::string& _name, unsigned _sample = 0);

private:

    RenderTargetManager(const ::Render::RenderWindow* const _renderWindow);

    ~RenderTargetManager();

};

}

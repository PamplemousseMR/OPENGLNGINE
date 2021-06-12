#pragma once

#include "OpenGLNgine/Core/IManager.hpp"

#include "OpenGLNgine/Hardware/RenderTarget.hpp"

namespace Hardware
{

class RenderTargetManager final : public ::Core::IManager< RenderTarget >
{

public:

    static RenderTargetManager& getInstance();

    RenderTargetManager(const RenderTargetManager&) = delete;

    RenderTargetManager(RenderTargetManager&&) = delete;

    RenderTargetManager& operator=(const RenderTargetManager&) = delete;

    RenderTargetManager& operator=(RenderTargetManager&&) = delete;

    RenderTargetPtr create(const std::string& _name, unsigned _sample = 0);

private:

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static RenderTargetManager* s_instance;

    RenderTargetManager();

    ~RenderTargetManager();

};

}

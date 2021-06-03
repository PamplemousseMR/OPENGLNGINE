#pragma once

#include "OpenGLNgine/Core/IManager.hpp"

#include "OpenGLNgine/Hardware/Compositor.hpp"

namespace Hardware
{

class CompositorManager final : public ::Core::IManager< Compositor >
{

public:

    static CompositorManager& getInstance();

    CompositorManager(const CompositorManager&) = delete;

    CompositorManager(CompositorManager&&) = delete;

    CompositorManager& operator=(const CompositorManager&) = delete;

    CompositorManager& operator=(CompositorManager&&) = delete;

    CompositorPtr create(const std::string& _name);

    CompositorPtr getByName(const std::string& _name);

    void destroy(const CompositorPtr& _compositor);

private:

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static CompositorManager* s_instance;

    CompositorManager();

    ~CompositorManager();

};

}

#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include <memory>

namespace Hardware
{

class Compositor;
class CompositorManager;

typedef std::shared_ptr< Compositor > CompositorPtr;

class Compositor final : public ::Core::IResource
{

public:

    Compositor(CompositorManager* const _manager, const std::string& _name);

    ~Compositor();

    Compositor(const Compositor&) = delete;

    Compositor(Compositor&&) = delete;

    Compositor& operator=(const Compositor&) = delete;

    Compositor& operator=(Compositor&&) = delete;

private:

    CompositorManager* const m_manager;

};

}

#pragma once

#include "OpenGLNgine/Core/IHardwareResource.hpp"

#include "OpenGLNgine/Hardware/CompositorTargetPass.hpp"

#include <memory>
#include <vector>

namespace Hardware
{

class Compositor;
class CompositorManager;

typedef std::shared_ptr< Compositor > CompositorPtr;

class Compositor final : public ::Core::IHardwareResource
{

    friend CompositorManager;

public:

    typedef std::vector< CompositorTargetPass* > CompositorTargetPassList;

    ~Compositor();

    Compositor(const Compositor&) = delete;

    Compositor(Compositor&&) = delete;

    Compositor& operator=(const Compositor&) = delete;

    Compositor& operator=(Compositor&&) = delete;

    CompositorTargetPass* createCompositorTargetPass();

    void destroyCompositorTargetPass(const CompositorTargetPass* const _pass);

    void destroyAllCompositorTargetPasses();

    inline const CompositorTargetPassList& getCompositorTargetPasses() const;

private:

    Compositor(CompositorManager* const _manager, const std::string& _name);

    CompositorTargetPassList m_compositorTargetPasses {};

};

inline const Compositor::CompositorTargetPassList& Compositor::getCompositorTargetPasses() const
{
    return m_compositorTargetPasses;
}

}

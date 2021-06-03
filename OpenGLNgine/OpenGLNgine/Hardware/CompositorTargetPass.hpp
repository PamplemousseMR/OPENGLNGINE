#pragma once

#include "OpenGLNgine/Hardware/CompositorPass.hpp"

#include <vector>

namespace Hardware
{

class Compositor;

class CompositorTargetPass
{

    friend Compositor;

public:

    typedef std::vector< CompositorPass* > CompositorPassList;

    CompositorTargetPass(const CompositorTargetPass&) = delete;

    CompositorTargetPass(CompositorTargetPass&&) = delete;

    CompositorTargetPass& operator=(const CompositorTargetPass&) = delete;

    CompositorTargetPass& operator=(CompositorTargetPass&&) = delete;

    CompositorPass* createCompositorPass();

    void destroyCompositorPass(CompositorPass* const _pass);

    void destroyAllCompositorPasses();

    inline const CompositorPassList& getCompositorPasses() const;

private:

    CompositorTargetPass();

    ~CompositorTargetPass();

    CompositorPassList m_compositorPasses {};

};

inline const CompositorTargetPass::CompositorPassList& CompositorTargetPass::getCompositorPasses() const
{
    return m_compositorPasses;
}

}

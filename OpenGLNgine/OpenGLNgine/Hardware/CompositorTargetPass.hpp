#pragma once

#include "OpenGLNgine/Hardware/CompositorPass.hpp"
#include "OpenGLNgine/Hardware/RenderTarget.hpp"

#include <vector>

namespace Hardware
{

enum COMPOSITORTARGETPASS_MODE
{
    CM_NONE,
    CM_PREVIOUS
};

enum COMPOSITORTARGETPASS_MASK
{
    CM_COLOR,
    CM_DEPTH,
    CM_STENCIL,
    CM_COLOR_DEPTH,
    CM_COLOR_STENCIL,
    CM_DEPTH_STENCIL,
    CM_ALL
};

enum COMPOSITORTARGETPASS_FILTER
{
    CF_LINEAR,
    CF_NEAREST
};

class Compositor;

class CompositorTargetPass
{

    friend Compositor;

public:

    static ::GL::FRAMBUFFER_MASK getType(COMPOSITORTARGETPASS_MASK _type);

    static ::GL::FRAMBUFFER_FILTER getType(COMPOSITORTARGETPASS_FILTER _type);

    typedef std::vector< CompositorPass* > CompositorPassList;

    CompositorTargetPass(const CompositorTargetPass&) = delete;

    CompositorTargetPass(CompositorTargetPass&&) = delete;

    CompositorTargetPass& operator=(const CompositorTargetPass&) = delete;

    CompositorTargetPass& operator=(CompositorTargetPass&&) = delete;

    CompositorPass* createCompositorPass(COMPOSITORPASS_TYPE _type);

    void destroyCompositorPass(CompositorPass* const _pass);

    void destroyAllCompositorPasses();

    inline const CompositorPassList& getCompositorPasses() const;

    COMPOSITORTARGETPASS_MODE m_mode { CM_NONE };

    COMPOSITORTARGETPASS_MASK m_mask { CM_COLOR };

    COMPOSITORTARGETPASS_FILTER m_filter { CF_NEAREST };

    RenderTargetPtr m_renderTarget { nullptr };

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

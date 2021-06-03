#pragma once

namespace Hardware
{

enum COMPOSITORPASS_TYPE
{
    CT_CLEAR
};

class CompositorTargetPass;

class CompositorPass
{

    friend CompositorTargetPass;

public:

    CompositorPass(const CompositorPass&) = delete;

    CompositorPass(CompositorPass&&) = delete;

    CompositorPass& operator=(const CompositorPass&) = delete;

    CompositorPass& operator=(CompositorPass&&) = delete;

    COMPOSITORPASS_TYPE m_type { CT_CLEAR };

private:

    CompositorPass();

    ~CompositorPass();

};

}

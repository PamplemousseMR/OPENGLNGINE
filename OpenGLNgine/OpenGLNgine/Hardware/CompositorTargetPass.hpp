#pragma once

namespace Hardware
{

class Compositor;

class CompositorTargetPass
{

    friend Compositor;

public:

    CompositorTargetPass(const CompositorTargetPass&) = delete;

    CompositorTargetPass(CompositorTargetPass&&) = delete;

    CompositorTargetPass& operator=(const CompositorTargetPass&) = delete;

    CompositorTargetPass& operator=(CompositorTargetPass&&) = delete;

private:

    CompositorTargetPass();

    ~CompositorTargetPass();

};

}

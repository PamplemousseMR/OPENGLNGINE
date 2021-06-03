#pragma once

namespace Hardware
{

class CompositorTargetPass;

class CompositorPass
{

    friend CompositorTargetPass;

public:

    CompositorPass(const CompositorPass&) = delete;

    CompositorPass(CompositorPass&&) = delete;

    CompositorPass& operator=(const CompositorPass&) = delete;

    CompositorPass& operator=(CompositorPass&&) = delete;

private:

    CompositorPass();

    ~CompositorPass();

};

}

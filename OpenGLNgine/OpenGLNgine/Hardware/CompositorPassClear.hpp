#pragma once

#include "OpenGLNgine/Hardware/CompositorPass.hpp"

namespace Hardware
{

class CompositorTargetPass;

class CompositorPassClear : CompositorPass
{

    friend CompositorTargetPass;

public:

    CompositorPassClear(const CompositorPassClear&) = delete;

    CompositorPassClear(CompositorPassClear&&) = delete;

    CompositorPassClear& operator=(const CompositorPassClear&) = delete;

    CompositorPassClear& operator=(CompositorPassClear&&) = delete;

private:

    CompositorPassClear();

    virtual ~CompositorPassClear();

};

}

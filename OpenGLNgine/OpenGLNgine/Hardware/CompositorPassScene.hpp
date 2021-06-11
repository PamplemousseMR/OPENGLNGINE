#pragma once

#include "OpenGLNgine/Hardware/CompositorPass.hpp"

namespace Hardware
{

class CompositorTargetPass;

class CompositorPassScene : CompositorPass
{

    friend CompositorTargetPass;

public:

    CompositorPassScene(const CompositorPassScene&) = delete;

    CompositorPassScene(CompositorPassScene&&) = delete;

    CompositorPassScene& operator=(const CompositorPassScene&) = delete;

    CompositorPassScene& operator=(CompositorPassScene&&) = delete;

private:

    CompositorPassScene();

    virtual ~CompositorPassScene();

};

}

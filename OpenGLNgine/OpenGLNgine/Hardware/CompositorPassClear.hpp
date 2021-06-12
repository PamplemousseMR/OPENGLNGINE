#pragma once

#include "OpenGLNgine/GL/DrawCall.hpp"
#include "OpenGLNgine/Hardware/CompositorPass.hpp"

#include <array>

namespace Hardware
{

enum COMPOSITORPASS_CLEAR
{
    CC_COLOR,
    CC_DEPTH,
    CC_STENCIL,
    CC_COLOR_DEPTH,
    CC_COLOR_STENCIL,
    CC_DEPTH_STENCIL,
    CC_ALL
};

class CompositorTargetPass;

class CompositorPassClear final : public CompositorPass
{

    friend CompositorTargetPass;

public:

    static ::GL::DRAWCALL_CLEAR getType(COMPOSITORPASS_CLEAR _type);

    CompositorPassClear(const CompositorPassClear&) = delete;

    CompositorPassClear(CompositorPassClear&&) = delete;

    CompositorPassClear& operator=(const CompositorPassClear&) = delete;

    CompositorPassClear& operator=(CompositorPassClear&&) = delete;

    inline void setClearColor(float _r, float _g, float _b, float _a);

    inline const std::array< float, 4 >& getClearColor() const;

    COMPOSITORPASS_CLEAR m_buffers { CC_COLOR_DEPTH };

    float m_depthClearValue { 1.f };

private:

    CompositorPassClear();

    virtual ~CompositorPassClear();

    std::array< float, 4 > m_clearColor { 0.f, 0.f, 0.f, 0.f };

};

inline void CompositorPassClear::setClearColor(float _r, float _g, float _b, float _a)
{
    m_clearColor = {_r, _g, _b, _a};
}

inline const std::array< float, 4 >& CompositorPassClear::getClearColor() const
{
    return m_clearColor;
}

}

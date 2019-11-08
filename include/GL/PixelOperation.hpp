#pragma once

#include <GL/glew.h>

namespace GL 
{

class PixelOperation
{

public:

    enum PIXELOPERATION_CLEAR : GLbitfield
    {
        CLEAR_COLOR = GL_COLOR_BUFFER_BIT,
        CLEAR_DEPTH = GL_DEPTH_BUFFER_BIT,
        CLEAR_STENCIL = GL_STENCIL_BUFFER_BIT,
        CLEAR_COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
        CLEAR_COLOR_STENCIL = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
        CLEAR_DEPTH_STENCIL = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
        CLEAR_ALL = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
    };

    enum PIXELOPERATION_DEPTH : GLenum
    {
        DEPTH_NEVER = GL_NEVER,
        DEPTH_LESS = GL_LESS,
        DEPTH_EQUAL = GL_EQUAL,
        DEPTH_LEQUAL = GL_LEQUAL,
        DEPTH_GREATER = GL_GREATER,
        DEPTH_NOTEQUAL = GL_NOTEQUAL,
        DEPTH_GEQUAL = GL_GEQUAL,
        DEPTH_ALWAYS = GL_ALWAYS
    };

    enum PIXELOPERATION_STENCIL_OPERATION : GLenum
    {
        STENCIL_KEEP = GL_KEEP,
        STENCIL_ZERO = GL_ZERO,
        STENCIL_REPLACE = GL_REPLACE,
        STENCIL_INCR = GL_INCR,
        STENCIL_INCR_WRAP = GL_INCR_WRAP,
        STENCIL_DECR = GL_DECR,
        STENCIL_DECR_WRAP = GL_DECR_WRAP,
        STENCIL_INVERT = GL_INVERT
    };

    enum PIXELOPERATION_STENCIL_FUNCTION : GLenum
    {
        STENCIL_NEVER = GL_NEVER,
        STENCIL_LESS = GL_LESS,
        STENCIL_LEQUAL = GL_LEQUAL,
        STENCIL_GREATER = GL_GREATER,
        STENCIL_GEQUAL = GL_GEQUAL,
        STENCIL_EQUAL = GL_EQUAL,
        STENCIL_NOTEQUAL = GL_NOTEQUAL,
        STENCIL_ALWAYS = GL_ALWAYS
    };

    enum PIXELOPERATION_BLEND : GLenum
    {
        BLEND_ZERO = GL_ZERO,
        BLEND_ONE = GL_ONE,
        BLEND_SRC_COLOR = GL_SRC_COLOR,
        BLEND_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
        BLEND_DST_COLOR = GL_DST_COLOR,
        BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        BLEND_SRC_ALPHA = GL_SRC_ALPHA,
        BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        BLEND_DST_ALPHA = GL_DST_ALPHA,
        BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
        BLEND_CONSTANT_COLOR = GL_CONSTANT_COLOR,
        BLEND_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
        BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
        BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
        BLEND_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
        BLEND_SRC1_COLOR = GL_SRC1_COLOR,
        BLEND_ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
        BLEND_SRC1_ALPHA = GL_SRC1_ALPHA,
        BLEND_ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA,
    };

public:

    static void clear(PIXELOPERATION_CLEAR) noexcept;

    static void setColorClearValue(float, float, float, float) noexcept;

    static void enableDepthTest(bool) noexcept;
    static void enableDepthWrite(bool) noexcept;
    static void setDepthFunc(PIXELOPERATION_DEPTH) noexcept;
    static void setDepthClearValue(float);
    static void setDepthClearValue(double);

    static void enableStencilTest(bool) noexcept;
    static void setStencilOperation(PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION) noexcept;
    static void setStencilFunc(PIXELOPERATION_STENCIL_FUNCTION, int, unsigned) noexcept;
    static void setStencilMask(unsigned) noexcept;
    static void seStencilClearValue(int);

    static void enableBlendTest(bool) noexcept;
    static void setBlendFunc(PIXELOPERATION_BLEND, PIXELOPERATION_BLEND) noexcept;

};

}


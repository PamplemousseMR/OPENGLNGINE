#pragma once

#include <GL/glew.h>

namespace GL 
{

class PixelOperation
{

public:

    enum PIXELOPERATION_CLEAR : GLbitfield
    {
        PC_COLOR = GL_COLOR_BUFFER_BIT,
        PC_DEPTH = GL_DEPTH_BUFFER_BIT,
        PC_STENCIL = GL_STENCIL_BUFFER_BIT,
        PC_COLOR_DEPTH = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
        PC_COLOR_STENCIL = GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
        PC_DEPTH_STENCIL = GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
        PC_ALL = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
    };

    enum PIXELOPERATION_DEPTH : GLenum
    {
        PD_NEVER = GL_NEVER,
        PD_LESS = GL_LESS,
        PD_EQUAL = GL_EQUAL,
        PD_LEQUAL = GL_LEQUAL,
        PD_GREATER = GL_GREATER,
        PD_NOTEQUAL = GL_NOTEQUAL,
        PD_GEQUAL = GL_GEQUAL,
        PD_ALWAYS = GL_ALWAYS
    };

    enum PIXELOPERATION_STENCIL_OPERATION : GLenum
    {
        PSO_KEEP = GL_KEEP,
        PSO_ZERO = GL_ZERO,
        PSO_REPLACE = GL_REPLACE,
        PSO_INCR = GL_INCR,
        PSO_INCR_WRAP = GL_INCR_WRAP,
        PSO_DECR = GL_DECR,
        PSO_DECR_WRAP = GL_DECR_WRAP,
        PSO_INVERT = GL_INVERT
    };

    enum PIXELOPERATION_STENCIL_FUNCTION : GLenum
    {
        PSF_NEVER = GL_NEVER,
        PSF_LESS = GL_LESS,
        PSF_LEQUAL = GL_LEQUAL,
        PSF_GREATER = GL_GREATER,
        PSF_GEQUAL = GL_GEQUAL,
        PSF_EQUAL = GL_EQUAL,
        PSF_NOTEQUAL = GL_NOTEQUAL,
        PSF_ALWAYS = GL_ALWAYS
    };

    enum PIXELOPERATION_BLEND : GLenum
    {
        PB_ZERO = GL_ZERO,
        PB_ONE = GL_ONE,
        PB_SRC_COLOR = GL_SRC_COLOR,
        PB_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
        PB_DST_COLOR = GL_DST_COLOR,
        PB_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
        PB_SRC_ALPHA = GL_SRC_ALPHA,
        PB_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
        PB_DST_ALPHA = GL_DST_ALPHA,
        PB_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
        PB_CONSTANT_COLOR = GL_CONSTANT_COLOR,
        PB_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
        PB_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
        PB_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
        PB_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
        PB_SRC1_COLOR = GL_SRC1_COLOR,
        PB_ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
        PB_SRC1_ALPHA = GL_SRC1_ALPHA,
        PB_ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA,
    };

public:

    static void clear(PIXELOPERATION_CLEAR);

    static void setColorClearValue(float, float, float, float);

    static void enableDepthTest(bool);
    static void enableDepthWrite(bool);
    static void setDepthFunc(PIXELOPERATION_DEPTH);
    static void setDepthClearValue(float);
    static void setDepthClearValue(double);

    static void enableStencilTest(bool);
    static void setStencilOperation(PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION);
    static void setStencilFunc(PIXELOPERATION_STENCIL_FUNCTION, int, unsigned);
    static void setStencilMask(unsigned);
    static void seStencilClearValue(int);

    static void enableBlendTest(bool);
    static void setBlendFunc(PIXELOPERATION_BLEND, PIXELOPERATION_BLEND);

};

}


#pragma once

#include <GL/glew.h>

namespace GL
{

/// Manages depth functions.
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

/// Manages stencil operations.
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

/// Manages stencil functions.
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

/// Manages blending operations.
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

/**
 * @brief Manages pixel operation state.
 */
class PixelOperation final
{

public:

    /**
     * @brief Specifies clear values for the color buffers.
     * @param _r Red value used when color buffers are cleared.
     * @param _g Green value used when color buffers are cleared.
     * @param _b Blue value used when color buffers are cleared.
     * @param _a Alpha value used when color buffers are cleared.
     */
    static void setColorClearValue(float _r, float _g, float _b, float _a);

    /**
     * @brief Enables and disables writing of frame buffer color components.
     * @param _r Red channel.
     * @param _g Green channel.
     * @param _b Blue channel
     * @param _a Alpha channel.
     */
    static void setColorMask(bool _r, bool _g, bool _b, bool _a);

    /**
     * @brief Enables or disables the depth comparison.
     * @param _enable State of the depth test.
     */
    static void enableDepthTest(bool _enable);

    /**
     * @brief Enable or disables writing into the depth buffer.
     * @param _enable State of the depth writing.
     */
    static void enableDepthWrite(bool _enable);

    /**
     * @brief Specifies the value used for depth buffer comparisons
     * @param _func Depth comparison function.
     */
    static void setDepthFunc(PIXELOPERATION_DEPTH _func);

    /**
     * @brief Specifies the clear value for the depth buffer
     * @param _value Depth value used when the depth buffer is cleared.
     */
    static void setDepthClearValue(float _value);

    /**
     * @brief Specifies the clear value for the depth buffer
     * @param _value Depth value used when the depth buffer is cleared.
     */
    static void setDepthClearValue(double _value);

    /**
     * @brief Enables or disables the stencil test.
     * @param _enable State of the stencil test.
     */
    static void enableStencilTest(bool _enable);

    /**
     * @brief Sets front and back stencil test actions.
     * @param _stencilFail Action to take when the stencil test fails.
     * @param _depthFail Sction when the stencil test passes, but the depth test fails.
     * @param _pass Sction when both the stencil test and the depth test pass, or when the stencil test passes and either there is no depth buffer or depth testing is not enabled.
     */
    inline static void setStencilOperation(PIXELOPERATION_STENCIL_OPERATION _stencilFail, PIXELOPERATION_STENCIL_OPERATION _depthFail, PIXELOPERATION_STENCIL_OPERATION _pass);

    /**
     * @brief Sets front and back function and reference value for stencil testing.
     * @param _func Test function.
     * @param _ref Reference value for the stencil test.
     * @param _mask Mask that is ANDed with both the reference value and the stored stencil value when the test is done.
     */
    static void setStencilFunc(PIXELOPERATION_STENCIL_FUNCTION _func, int _ref, unsigned _mask);

    /**
     * @brief Control the front and back writing of individual bits in the stencil planes.
     * @param _mask Bit mask to enable and disable writing of individual bits in the stencil planes.
     */
    static void setStencilMask(unsigned _mask);

    /**
     * @brief Specifies the clear value for the stencil buffer
     * @param _value Index used when the stencil buffer is cleared.
     */
    static void seStencilClearValue(int _value);

    /**
     * @brief Enables or disables the blending the computed fragment color values with the values in the color buffers.
     * @param _enable State of the blending test.
     */
    static void enableBlendTest(bool _enable);

    /**
     * @brief Specifies pixel blending arithmetic.
     * @param _sfactor How the red, green, blue, and alpha source blending factors are computed.
     * @param _dfactor How the red, green, blue, and alpha destination blending factors are computed.
     */
    static void setBlendFunc(PIXELOPERATION_BLEND _sfactor, PIXELOPERATION_BLEND _dfactor);

};

}

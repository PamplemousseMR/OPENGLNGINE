#include "OpenGLNgine/GL/PixelOperation.hpp"

namespace GL
{

void PixelOperation::setColorClearValue(float _r, float _g, float _b, float _a)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::array< float, 4 > s_cache = {0.f, 0.f, 0.f, 0.f};
    if(_r != s_cache[0] || _g != s_cache[1] || _b != s_cache[2] || _a != s_cache[3])
    {
        s_cache = {_r, _g, _b, _a};
        glClearColor(_r, _g, _b, _a);
        GLNGINE_CHECK_GL;
    }
#else
    glClearColor(_r, _g, _b, _a);
#endif
}

void PixelOperation::setColorMask(bool _r, bool _g, bool _b, bool _a)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::array< bool, 4 > s_cache = {true, true, true, true};
    if(_r != s_cache[0] || _g != s_cache[1] || _b != s_cache[2] || _a != s_cache[3])
    {
        s_cache = {_r, _g, _b, _a};
        glColorMask(_r, _g, _b, _a);
        GLNGINE_CHECK_GL;
    }
#else
    glColorMask(_r, _g, _b, _a);
#endif
}

void PixelOperation::enableDepthTest(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        _enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        GLNGINE_CHECK_GL;
    }
#else
    _enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
#endif
}

void PixelOperation::enableDepthWrite(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        glDepthMask(_enable ? GL_TRUE : GL_FALSE);
        GLNGINE_CHECK_GL;
    }
#else
    glDepthMask(_enable ? GL_TRUE : GL_FALSE);
#endif
}

void PixelOperation::setDepthFunc(PIXELOPERATION_DEPTH _func)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static PIXELOPERATION_DEPTH s_cache = PD_LESS;
    if(s_cache != _func)
    {
        s_cache = _func;
        glDepthFunc(_func);
        GLNGINE_CHECK_GL;
    }
#else
    glDepthFunc(_func);
#endif
}

void PixelOperation::setDepthClearValue(float _value)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static float s_cache = 1.f;
    if(s_cache != _value)
    {
        s_cache = _value;
        glClearDepthf(_value);
        GLNGINE_CHECK_GL;
    }
#else
    glClearDepthf(_value);
#endif
}

void PixelOperation::setDepthClearValue(double _value)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static double s_cache = 1.;
    if(s_cache != _value)
    {
        s_cache = _value;
        glClearDepth(_value);
        GLNGINE_CHECK_GL;
    }
#else
    glClearDepth(_value);
#endif
}

void PixelOperation::enableStencilTest(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        _enable ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
        GLNGINE_CHECK_GL;
    }
#else
    _enable ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
#endif
}

void PixelOperation::setStencilOperation(PIXELOPERATION_STENCIL_OPERATION _stencilFail, PIXELOPERATION_STENCIL_OPERATION _depthFail, PIXELOPERATION_STENCIL_OPERATION _pass)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::tuple<PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION, PIXELOPERATION_STENCIL_OPERATION > s_cache = {PSO_KEEP, PSO_KEEP, PSO_KEEP};
    const auto values = std::make_tuple(_stencilFail, _depthFail, _pass);
    if(s_cache != values)
    {
        s_cache = values;
        glStencilOp(_stencilFail, _depthFail, _pass);
        GLNGINE_CHECK_GL;
    }
#else
    glStencilOp(_stencilFail, _depthFail, _pass);
#endif
}

void PixelOperation::setStencilFunc(PIXELOPERATION_STENCIL_FUNCTION _func, int _ref, unsigned _mask)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::tuple<PIXELOPERATION_STENCIL_FUNCTION, int, unsigned > s_cache = {PSF_ALWAYS, 0, 0xFF};
    const auto values = std::make_tuple(_func, _ref, _mask);
    if(s_cache != values)
    {
        s_cache = values;
        glStencilFunc(_func, _ref, _mask);
        GLNGINE_CHECK_GL;
    }
#else
    glStencilFunc(_func, _ref, _mask);
#endif
}

void PixelOperation::setStencilMask(unsigned _mask)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static unsigned s_cache = 0xFF;
    if(s_cache != _mask)
    {
        s_cache = _mask;
        glStencilMask(_mask);
        GLNGINE_CHECK_GL;
    }
#else
    glStencilMask(_mask);
#endif
}

void PixelOperation::seStencilClearValue(int _value)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static int s_cache = 0;
    if(s_cache != _value)
    {
        s_cache = _value;
        glClearStencil(_value);
        GLNGINE_CHECK_GL;
    }
#else
    glClearStencil(_value);
#endif
}

void PixelOperation::enableBlendTest(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        _enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        GLNGINE_CHECK_GL;
    }
#else
    _enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
#endif
}

void PixelOperation::setBlendFunc(PIXELOPERATION_BLEND _sfactor, PIXELOPERATION_BLEND _dfactor)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::pair<PIXELOPERATION_BLEND, PIXELOPERATION_BLEND > s_cache = {PB_ONE, PB_ZERO};
    const auto values = std::make_pair(_sfactor, _dfactor);
    if(s_cache != values)
    {
        s_cache = values;
        glBlendFunc(_sfactor, _dfactor);
        GLNGINE_CHECK_GL;
    }
#else
    glBlendFunc(_sfactor, _dfactor);
#endif
}

}

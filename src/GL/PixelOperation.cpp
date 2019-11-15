#include "GL/PixelOperation.hpp"

namespace GL
{

    void PixelOperation::clear(PIXELOPERATION_CLEAR _mask)
    {
        glClear(_mask);
    }

    void PixelOperation::setColorClearValue(float _r, float _g, float _b, float _a)
    {
        glClearColor(_r, _g, _b, _a);
    }

    void PixelOperation::enableDepthTest(bool _enable)
    {
        _enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }

    void PixelOperation::enableDepthWrite(bool _enable)
    {
        glDepthMask(_enable ? GL_TRUE : GL_FALSE);
    }

   void PixelOperation::setDepthFunc(PIXELOPERATION_DEPTH _func)
   {
       glDepthFunc(_func);
   }

   void PixelOperation::setDepthClearValue(float _value)
   {
       glClearDepthf(_value);
   }

   void PixelOperation::setDepthClearValue(double _value)
   {
       glClearDepth(_value);
   }

   void PixelOperation::enableStencilTest(bool _enable)
   {
       _enable ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
   }

   void PixelOperation::setStencilOperation(PIXELOPERATION_STENCIL_OPERATION _stencilFail, PIXELOPERATION_STENCIL_OPERATION _depthFail, PIXELOPERATION_STENCIL_OPERATION _pass)
   {
       glStencilOp(_stencilFail, _depthFail, _pass);
   }

   void PixelOperation::setStencilFunc(PIXELOPERATION_STENCIL_FUNCTION _func, int _ref, unsigned _mask)
   {
       glStencilFunc(_func, _ref, _mask);
   }

    void PixelOperation::setStencilMask(unsigned _mask)
    {
        glStencilMask(_mask);
    }

    void PixelOperation::seStencilClearValue(int _value)
    {
        glClearStencil(_value);
    }

    void PixelOperation::enableBlendTest(bool _enable)
    {
        _enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    }

    void PixelOperation::setBlendFunc(PIXELOPERATION_BLEND _sfactor, PIXELOPERATION_BLEND _dfactor)
    {
        glBlendFunc(_sfactor, _dfactor);
    }

}

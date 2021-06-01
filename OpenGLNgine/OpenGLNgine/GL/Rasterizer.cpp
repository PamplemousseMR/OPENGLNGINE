#include "OpenGLNgine/GL/Rasterizer.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <array>
#include <tuple>

namespace GL
{

GLint Rasterizer::s_MAX_SIZE[2] = {0, 0};

void Rasterizer::setViewport(int _x, int _y, int _width, int _height)
{
    const static Initializer s_INITIALIZER;
    if(_width > s_MAX_SIZE[0] || _height > s_MAX_SIZE[1])
    {
        GLNGINE_EXCEPTION("Viewport size too large");
    }
#ifdef GLNGINE_USE_STATE_CACHE
    static std::array< int, 4 > s_cache = {-1, -1, -1, -1};
    if(_x != s_cache[0] || _y != s_cache[1] || _width != s_cache[2] || _height != s_cache[3])
    {
        s_cache = {_x, _y, _width, _height};
        glViewport(_x, _y, _width, _height);
        GLNGINE_CHECK_GL;
    }
#else
    glViewport(_x, _y, _width, _height);
#endif
}

void Rasterizer::enableScissorTest(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        _enable ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
        GLNGINE_CHECK_GL;
    }
#else
    _enable ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
#endif
}

void Rasterizer::setScissor(int _x, int _y, int _width, int _height)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static std::tuple<int, int, int, int > s_cache = {-1, -1, -1, -1};
    const auto values = std::make_tuple(_x, _y, _width, _height);
    if(s_cache != values)
    {
        s_cache = values;
        glScissor(_x, _y, _width, _height);
        GLNGINE_CHECK_GL;
    }
#else
    glScissor(_x, _y, _width, _height);
#endif
}

void Rasterizer::enableCulling(bool _enable)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static bool s_cache = false;
    if(s_cache != _enable)
    {
        s_cache = _enable;
        _enable ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        GLNGINE_CHECK_GL;
    }
#else
    _enable ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
#endif
}

void Rasterizer::setCullFace(RASTERIZER_CULLFACE _cullface)
{
#ifdef GLNGINE_USE_STATE_CACHE
    static RASTERIZER_CULLFACE s_cache = RC_BACK;
    if(s_cache != _cullface)
    {
        s_cache = _cullface;
        glCullFace(_cullface);
        GLNGINE_CHECK_GL;
    }
#else
    glCullFace(_cullface);
#endif
}

Rasterizer::Initializer::Initializer()
{
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, s_MAX_SIZE);
    GLNGINE_CHECK_GL;
}

}

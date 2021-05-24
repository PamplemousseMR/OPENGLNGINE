#include "OpenGLNgine/GL/Rasterizer.hpp"

#include <array>

namespace GL
{

GLint Rasterizer::s_MAX_SIZE[2] = {0, 0};

void Rasterizer::setViewport(int _x, int _y, int _width, int _height)
{
    const static Initializer s_INITIALIZER;
    if(_width > s_MAX_SIZE[0] || _height > s_MAX_SIZE[1])
    {
        GLNGINE_EXCEPTION("The size too big");
    }
    static std::array< int, 4 > s_cache = {-1, -1, -1, -1};
    if(_x != s_cache[0] || _y != s_cache[1] || _width != s_cache[2] || _height != s_cache[3])
    {
        s_cache = {_x, _y, _width, _height};
        glViewport(_x, _y, _width, _height);
        GLNGINE_CHECK_GL;
    }
}


Rasterizer::Initializer::Initializer()
{
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, s_MAX_SIZE);
    GLNGINE_CHECK_GL;
}

}

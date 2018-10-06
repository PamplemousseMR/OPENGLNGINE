#include "GL/Viewport.hpp"

#include <assert.h>
#include <stdexcept>

using namespace std;
using namespace glm;

namespace GL
{
    std::vector< std::function< void(int, int) > > Viewport::s_listeners = {};
    int Viewport::s_width = 0;
    int Viewport::s_height = 0;
    GLint Viewport::s_maxSize[2] = {0, 0};
    bool Viewport::s_first = true;

    void Viewport::setViewport(int _width, int _height)
    {
        if (s_first)
        {
            s_first = false;
            glGetIntegerv(GL_MAX_VIEWPORT_DIMS, s_maxSize);
        }
        if(_width > s_maxSize[0] || _height > s_maxSize[1])
        {
            throw overflow_error("[Viewport] Size too big");
        }
        s_width = _width;
        s_height = _height;
        glViewport(0, 0, _width, _height);
        assert(glGetError() == GL_NO_ERROR);
        for(Listener l : s_listeners)
        {
            l(_width, _height);
        }
    }

    int Viewport::getWidth()
    {
        return s_width;
    }

    int Viewport::getHeight()
    {
        return s_height;
    }

    glm::vec2 Viewport::getViewport()
    {
        return vec2(s_width, s_height);
    }

    void Viewport::addListener(const Listener& _listener)
    {
        s_listeners.push_back(_listener);
    }

    void Viewport::init(int _width, int _height)
    {
        s_width = _width;
        s_height = _height;
    }

}

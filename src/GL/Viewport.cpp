#include "GL/Viewport.hpp"

#include <assert.h>
#include <stdexcept>

using namespace std;

namespace GL
{
    std::vector< std::function< void(int, int) > > Viewport::s_listeners = {};
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
        glViewport(0, 0, _width, _height);
        for(Listener l : s_listeners)
        {
            l(_width, _height);
        }
        assert(glGetError() == GL_NO_ERROR);
    }

    void Viewport::addListener(const Listener& _listener)
    {
        s_listeners.push_back(_listener);
    }
}

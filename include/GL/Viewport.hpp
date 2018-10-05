#pragma once

#include <GL/glew.h>

#include <functional>
#include <vector>

namespace GL 
{

class Viewport
{

public:

    typedef std::function< void(int, int) > Listener;

public:

    static void setViewport(int, int);
    static void addListener(const Listener&);

private:

    static std::vector< Listener > s_listeners;
    static GLint s_maxSize[2];
    static bool s_first;

};

}


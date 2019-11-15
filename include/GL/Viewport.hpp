#pragma once

#include <GL/glew.h>

#include <glm/vec2.hpp>

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
    static int getWidth();
    static int getHeight();
    static glm::vec2 getViewport();

private:

    static std::vector< Listener > s_listeners;
    static int s_width;
    static int s_height;
    static GLint s_maxSize[2];
    static bool s_first;

};

}


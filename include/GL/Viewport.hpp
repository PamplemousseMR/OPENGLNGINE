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
    static void addListener(const Listener&) noexcept;
    static int getWidth() noexcept;
    static int getHeight() noexcept;
    static glm::vec2 getViewport() noexcept;

private:

    static std::vector< Listener > s_listeners;
    static int s_width;
    static int s_height;
    static GLint s_maxSize[2];
    static bool s_first;

};

}


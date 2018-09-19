#pragma once

#include <GL/glew.h>

namespace GL 
{

class Viewport
{

public:

    static void setViewport(int, int);

private:

    static GLint s_maxSize[2];
    static bool s_first;

};

}


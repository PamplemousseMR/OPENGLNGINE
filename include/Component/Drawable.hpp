#pragma once

#include <GL/glew.h>

#include "Component.hpp"

namespace Component
{
class Drawable : public Component
{

public:

    static const GLuint S_VERTEXLOCATION;
    static const GLuint S_TEXTCOORDLOCATION;
    static const GLuint S_NORMALLOCATION;

public :

    Drawable(const std::string&);
    virtual ~Drawable();
    Drawable(const Drawable&);
    Drawable(Drawable&&);
    Drawable& operator=(const Drawable&);
    Drawable& operator=(Drawable&&);

};

}

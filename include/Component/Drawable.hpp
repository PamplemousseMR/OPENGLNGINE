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

    inline GLuint getVertexLocation() const;
    inline GLuint getTextureCoordLocation() const;
    inline GLuint getNormalLocation() const;
};

inline GLuint Drawable::getVertexLocation() const
{
    return S_VERTEXLOCATION;
}

inline GLuint Drawable::getTextureCoordLocation() const
{
    return S_TEXTCOORDLOCATION;
}

inline GLuint Drawable::getNormalLocation() const
{
    return S_NORMALLOCATION;
}

}

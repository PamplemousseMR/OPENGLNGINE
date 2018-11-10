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

    inline GLuint getVertexLocation() const noexcept;
    inline GLuint getTextureCoordLocation() const noexcept;
    inline GLuint getNormalLocation() const noexcept;
};

inline GLuint Drawable::getVertexLocation() const noexcept
{
    return S_VERTEXLOCATION;
}

inline GLuint Drawable::getTextureCoordLocation() const noexcept
{
    return S_TEXTCOORDLOCATION;
}

inline GLuint Drawable::getNormalLocation() const noexcept
{
    return S_NORMALLOCATION;
}

}

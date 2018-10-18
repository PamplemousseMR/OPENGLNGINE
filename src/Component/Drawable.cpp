#include "Component/Drawable.hpp"

using namespace std;

namespace Component
{
    const GLuint Drawable::S_VERTEXLOCATION = 0;
    const GLuint Drawable::S_TEXTCOORDLOCATION = 1;
    const GLuint Drawable::S_NORMALLOCATION = 2;

    Drawable::Drawable(const string& _name) :
        Component(_name)
    {
    }

    Drawable::~Drawable()
    {
    }

    Drawable::Drawable(const Drawable& _drawable) :
        Component(_drawable)
    {
    }

    Drawable::Drawable(Drawable&& _drawable) :
        Component(move(_drawable))
    {
    }

    Drawable& Drawable::operator=(const Drawable& _drawable)
    {
        if(this != &_drawable)
        {
            Component::operator=(_drawable);
        }
        return *this;
    }

    Drawable& Drawable::operator=(Drawable&& _drawable)
    {
        if(this != &_drawable)
        {
            Component::operator=(move(_drawable));
        }
        return *this;
    }
}

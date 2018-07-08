#pragma once

#include <GL/glew.h>

#include <iostream>
#include <vector>

namespace GL
{

class Shader;

class Program
{

public:

    Program();
    ~Program();

    void attach(Shader* shader);
    void detach(Shader* shader);
    void detachAll();
    void link() const throw(...);
    void toggle();

    bool isActive() const;
    GLuint getId() const;

private:

    GLuint m_id;
    bool m_toggled;
    std::vector<Shader*> m_shaders;

};

}

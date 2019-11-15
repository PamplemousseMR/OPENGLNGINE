#pragma once

#include "Drawable.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>

namespace GL
{
    class VertexBuffer;
    class VertexArrayBuffer;
    class ElementsBuffer;
}

namespace Component
{

class Quad : public Drawable
{

public:

    Quad(const std::string&);
    ~Quad();
    Quad(const Quad&);
    Quad(Quad&&);
    Quad& operator=(const Quad&);
    Quad& operator=(Quad&&);

    inline void draw() const;

    void bind() const;
    void unbind() const;

    std::ostream& print(std::ostream&) const;

private:

    static const int s_TD_SIZE {6};

    const std::vector< glm::vec3 > s_VERTICES = {
        {-1.0, -1.0, 0.0},
        {1.0, -1.0, 0.0},
        {1.0, 1.0, 0.0},
        {-1.0, -1.0, 0.0},
        {1.0, 1.0, 0.0},
        {-1.0, 1.0, 0.0}
    };

private:

    GL::VertexBuffer* m_vboVertex {nullptr};
    GL::VertexArrayBuffer* m_vao {nullptr};

};

std::ostream& operator<<(std::ostream&, const Quad&);

inline void Quad::draw() const
{
    glDrawArrays(GL_TRIANGLES, 0, s_TD_SIZE);
    assert(glGetError() == GL_NO_ERROR);
}

}

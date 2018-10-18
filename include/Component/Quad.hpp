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
    ~Quad() noexcept;
    Quad(const Quad&);
    Quad(Quad&&);
    Quad& operator=(const Quad&);
    Quad& operator=(Quad&&);

    inline void draw() const noexcept;

    void bind() const noexcept;
    void unbind() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    static const int s_DATA_SIZE {6};

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

std::ostream& operator<<(std::ostream&, const Quad&) noexcept;

inline void Quad::draw() const noexcept
{
    glDrawArrays(GL_TRIANGLES, 0, s_DATA_SIZE);
    assert(glGetError() == GL_NO_ERROR);
}

}

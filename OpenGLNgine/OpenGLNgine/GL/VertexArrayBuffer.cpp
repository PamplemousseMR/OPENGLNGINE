#include "OpenGLNgine/GL/VertexArrayBuffer.hpp"

using namespace std;

namespace GL
{
VertexArrayBuffer::VertexArrayBuffer() :
    IBindable()
{
    glGenVertexArrays(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the vertex array buffer");
    }
}

VertexArrayBuffer::~VertexArrayBuffer()
{
    glDeleteVertexArrays(1, &m_id);
}
}

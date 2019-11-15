#include "GL/VertexArrayBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    VertexArrayBuffer::VertexArrayBuffer() :
        IBindable()
    {
        glGenVertexArrays(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        if(m_id == 0)
        {
            throw overflow_error("[VertexArrayBuffer] Out of memory");
        }
    }

    VertexArrayBuffer::~VertexArrayBuffer()
    {
        glDeleteBuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
    }
}

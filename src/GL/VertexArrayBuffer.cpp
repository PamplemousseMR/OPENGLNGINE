#include "GL/VertexArrayBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    VertexArrayBuffer::VertexArrayBuffer() :
        IGLObject()
    {
        glGenVertexArrays(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[VertexArrayBuffer] Out of memory");
        }
    }

    VertexArrayBuffer::~VertexArrayBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }
}

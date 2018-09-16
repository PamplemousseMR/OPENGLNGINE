#include "GL/VertexArrayBuffer.hpp"

using namespace std;

namespace GL
{
    VertexArrayBuffer::VertexArrayBuffer()
    {
        glGenVertexArrays(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[VertexBuffer] Out of memory");
        }
    }

    VertexArrayBuffer::~VertexArrayBuffer() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }
}

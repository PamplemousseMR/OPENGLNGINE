#include "GL/RenderBuffer.hpp"

using namespace std;

namespace GL
{
    RenderBuffer::RenderBuffer()
    {
        glGenRenderbuffers(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[RenderBuffer] Out of memory");
        }
    }

    RenderBuffer::~RenderBuffer() noexcept
    {
        glDeleteRenderbuffers(1, &m_id);
    }

    RenderBuffer::RenderBuffer(const RenderBuffer&)
    {
        throw invalid_argument("[RenderBuffer] TODO");
    }

    RenderBuffer& RenderBuffer::operator=(const RenderBuffer&)
    {
        throw invalid_argument("[RenderBuffer] TODO");
        return *this;
    }
}

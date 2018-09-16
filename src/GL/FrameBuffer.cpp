#include "GL/FrameBuffer.hpp"

using namespace std;

namespace GL
{
    FrameBuffer::FrameBuffer()
    {
        glGenFramebuffers(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[FrameBuffer] Out of memory");
        }
    }

    FrameBuffer::~FrameBuffer() noexcept
    {
        glDeleteFramebuffers(1, &m_id);
    }

    FrameBuffer::FrameBuffer(const FrameBuffer&)
    {
        throw invalid_argument("[FrameBuffer] TODO");
    }

    FrameBuffer& FrameBuffer::operator=(const FrameBuffer&)
    {
        throw invalid_argument("[FrameBuffer] TODO");
        return *this;
    }
}

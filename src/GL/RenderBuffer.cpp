#include "GL/RenderBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    RenderBuffer::RenderBuffer() :
        IGLObject()
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

    RenderBuffer::RenderBuffer(const RenderBuffer& _renderBuffer) :
        IGLObject(_renderBuffer)
    {
        throw invalid_argument("[RenderBuffer] TODO");
    }

    RenderBuffer& RenderBuffer::operator=(const RenderBuffer& _renderBuffer)
    {
        if(this != &_renderBuffer)
        {
            glDeleteRenderbuffers(1, &m_id);
            IGLObject::operator=(_renderBuffer);
            throw invalid_argument("[RenderBuffer] TODO");
        }
        return *this;
    }

}

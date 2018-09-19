#include "GL/RenderBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    RenderBuffer::RenderBuffer() :
        IGLObject()
    {
        glGenRenderbuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        if(m_id == 0)
        {
            throw overflow_error("[RenderBuffer] Out of memory");
        }
    }

    RenderBuffer::~RenderBuffer() noexcept
    {
        glDeleteRenderbuffers(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
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
            assert(glGetError() == GL_NO_ERROR);
            IGLObject::operator=(_renderBuffer);
            throw invalid_argument("[RenderBuffer] TODO");
        }
        return *this;
    }

}

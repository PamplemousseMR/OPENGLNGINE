#include "GL/RenderBuffer.hpp"

#include <stdexcept>

using namespace std;

namespace GL
{
    GLint RenderBuffer::s_maxSize = 0;
    bool RenderBuffer::s_first = true;

    RenderBuffer::RenderBuffer() :
        IGLObject()
    {
        if(s_first)
        {
            s_first = false;
            glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &s_maxSize);
        }
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
            throw invalid_argument("[RenderBuffer] TODO");
        }
        return *this;
    }

    void RenderBuffer::allocate(int _width, int _height, RENDERBUFFER_FORMAT _format) const
    {
        if(_width > s_maxSize || _height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        glRenderbufferStorage(GL_RENDERBUFFER, _format, _width, _height);
        assert(glGetError() == GL_NO_ERROR);
    }
}

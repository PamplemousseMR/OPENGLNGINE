#include "GL/FrameBuffer.hpp"
#include "GL/Texture.hpp"
#include "GL/RenderBuffer.hpp"

#include <exception>

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

    void FrameBuffer::attachColorTexture2D(const GL::Texture* const _texture, unsigned _attach) const
    {
        GLint maxAttach = 0;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
        if(_attach >= unsigned(maxAttach))
        {
            throw overflow_error("[FrameBuffer] Too much attached texture");
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_TEXTURE_2D, _texture->getId(), 0);
    }

    void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer* const _buffer) const noexcept
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer->getId());
    }

    void FrameBuffer::checkStatus() const
    {
        GLenum err;
        if((err = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
        {
            switch(err) {
            case GL_FRAMEBUFFER_UNDEFINED:
                throw std::runtime_error("[FrameBuffer] undefined");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                throw std::runtime_error("[FrameBuffer] incomplete attachment");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                throw std::runtime_error("[FrameBuffer] incomplete missing attachment");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                throw std::runtime_error("[FrameBuffer] incomplete draw buffer");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                throw std::runtime_error("[FrameBuffer] incomplete read buffer");
                break;
            case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
                throw std::runtime_error("[FrameBuffer] attachment object type");
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                throw std::runtime_error("[FrameBuffer] unsupported");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                throw std::runtime_error("[FrameBuffer] incomplete multisample");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                throw std::runtime_error("[FrameBuffer] incomplete layer targets");
                break;
            }
        }
    }

}

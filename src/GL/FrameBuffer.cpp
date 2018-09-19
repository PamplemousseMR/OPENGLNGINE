#include "GL/FrameBuffer.hpp"

#include <algorithm>
#include <stdexcept>

using namespace std;

namespace GL
{
    FrameBuffer::FrameBuffer() :
        IGLObject()
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

    FrameBuffer::FrameBuffer(const FrameBuffer& _frameBuffer) :
        IGLObject(_frameBuffer)
    {
        throw invalid_argument("[FrameBuffer] TODO");
    }

    FrameBuffer& FrameBuffer::operator=(const FrameBuffer& _frameBuffer)
    {
        if(this != &_frameBuffer)
        {
            glDeleteFramebuffers(1, &m_id);
            IGLObject::operator=(_frameBuffer);
            throw invalid_argument("[FrameBuffer] TODO");
        }
        return *this;
    }

    void FrameBuffer::attachColorTexture2D(const GL::Texture& _texture, unsigned _attach)
    {
        GLint maxAttach = 0;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
        if(_attach >= unsigned(maxAttach))
        {
            throw overflow_error("[FrameBuffer] Too much attached texture");
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_TEXTURE_2D, _texture.getId(), 0);
        auto p = find(m_colorAttachement.begin(), m_colorAttachement.end(), _attach);
        if (p == m_colorAttachement.end())
        {
            m_colorAttachement.push_back(_attach);
        }
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

    void FrameBuffer::attachDrawBuffers() const noexcept
    {
        std::vector< GLenum > drawBuffers(m_colorAttachement.size());
        for(size_t i=0 ; i<m_colorAttachement.size() ; ++i)
        {
            drawBuffers[i] = GL_COLOR_ATTACHMENT0 + m_colorAttachement[i];
        }
        glDrawBuffers(GLsizei(m_colorAttachement.size()), &drawBuffers[0]);
    }

}

#include "OpenGLNgine/GL/FrameBuffer.hpp"

#include <algorithm>
#include <stdexcept>

namespace GL
{

GLint FrameBuffer::s_MAX_ATTACHEMENT = 0;

GLint FrameBuffer::s_MAX_DRAW = 0;

ptrdiff_t FrameBuffer::s_defaultCache = reinterpret_cast< ptrdiff_t >(nullptr);

FrameBuffer::FrameBuffer() :
    IBindable()
{
    static const Initializer s_INITIALIZER;
    glGenFramebuffers(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the frame buffer");
    }
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_id);
}

void FrameBuffer::attachColorTexture(const Texture& _texture, unsigned _attach)
{
    if(_attach >= unsigned(s_MAX_ATTACHEMENT))
    {
        GLNGINE_EXCEPTION("Can't attach a texture to this index");
    }
    switch(_texture.getType())
    {
    case TT_1D:
        glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_TEXTURE_1D, _texture.getId(), 0);
        break;
    case TT_2D:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_TEXTURE_2D, _texture.getId(), 0);
        break;
    case TT_2DMULTISAMPLE:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_TEXTURE_2D_MULTISAMPLE, _texture.getId(), 0);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
    auto p = find(m_colorAttachement.begin(), m_colorAttachement.end(), _attach);
    if(p == m_colorAttachement.end())
    {
        m_colorAttachement.push_back(_attach);
    }
}

void FrameBuffer::attachDepthTexture(const Texture& _texture) const
{
    switch(_texture.getType())
    {
    case TT_1D:
        glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_1D, _texture.getId(), 0);
        break;
    case TT_2D:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texture.getId(), 0);
        break;
    case TT_2DMULTISAMPLE:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _texture.getId(), 0);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
}

void FrameBuffer::attachDepthStencilTexture(const Texture& _texture) const
{
    switch(_texture.getType())
    {
    case TT_1D:
        glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_1D, _texture.getId(), 0);
        break;
    case TT_2D:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _texture.getId(), 0);
        break;
    case TT_2DMULTISAMPLE:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _texture.getId(), 0);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
}

void FrameBuffer::attachColorBuffer(const RenderBuffer& _buffer, unsigned _attach)
{
    if(_attach >= unsigned(s_MAX_ATTACHEMENT))
    {
        GLNGINE_EXCEPTION("Can't attach a buffer to this index");
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attach, GL_RENDERBUFFER, _buffer.getId());
    GLNGINE_CHECK_GL;
    auto p = find(m_colorAttachement.begin(), m_colorAttachement.end(), _attach);
    if(p == m_colorAttachement.end())
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
            GLNGINE_EXCEPTION("Default frame buffer doesn't exist");
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            GLNGINE_EXCEPTION("Incomplete attachement");
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            GLNGINE_EXCEPTION("Missing attachement");
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            GLNGINE_EXCEPTION("Incomplete draw buffer");
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            GLNGINE_EXCEPTION("Incomplete read buffer");
        case GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE:
            GLNGINE_EXCEPTION("Attachment object type");
        case GL_FRAMEBUFFER_UNSUPPORTED:
            GLNGINE_EXCEPTION("Unsupported");
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            GLNGINE_EXCEPTION("Incomplete multisample");
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            GLNGINE_EXCEPTION("Incomplete layer targets");
        default:
            GLNGINE_EXCEPTION("Unhandle frame buffer error");
        }
    }
    GLNGINE_CHECK_GL;
}

void FrameBuffer::attachDrawBuffers() const
{
    if(m_colorAttachement.size() >= unsigned(s_MAX_DRAW))
    {
        GLNGINE_EXCEPTION("Too much draw texture");
    }
    std::vector< GLenum > drawBuffers(m_colorAttachement.size());
    for(size_t i=0 ; i<m_colorAttachement.size() ; ++i)
    {
        drawBuffers[i] = GL_COLOR_ATTACHMENT0 + m_colorAttachement[i];
    }
    glDrawBuffers(GLsizei(m_colorAttachement.size()), &drawBuffers[0]);
    GLNGINE_CHECK_GL;
}

void FrameBuffer::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_defaultCache != add)
    {
        s_defaultCache = add;
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }
#else
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
#endif
}

void FrameBuffer::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_defaultCache != add)
    {
        s_defaultCache = add;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
#else
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}

void FrameBuffer::bindDraw() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
}

void FrameBuffer::bindRead() const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
}

FrameBuffer::Initializer::Initializer()
{
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &s_MAX_ATTACHEMENT);
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &s_MAX_DRAW);
}
}

#include "OpenGLNgine/GL/RenderBuffer.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

namespace GL
{

GLint RenderBuffer::s_MAX_SIZE = 0;
GLint RenderBuffer::s_MAX_SAMPLE = 0;

ptrdiff_t RenderBuffer::s_cache = reinterpret_cast< ptrdiff_t >(nullptr);

RenderBuffer::RenderBuffer() :
    IBindable()
{
    const static Initializer s_INITIALIZER;
    glGenRenderbuffers(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the render buffer");
    }
}

RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1, &m_id);
}

RenderBuffer::RenderBuffer(const RenderBuffer& _renderBuffer) :
    IBindable(_renderBuffer)
{
    GLNGINE_EXCEPTION("TODO");
}

RenderBuffer& RenderBuffer::operator=(const RenderBuffer& _renderBuffer)
{
    if(this != &_renderBuffer)
    {
        GLNGINE_EXCEPTION("TODO");
    }
    return *this;
}

void RenderBuffer::allocate(int _width, int _height, RENDERBUFFER_FORMAT _format) const
{
    if(_width > s_MAX_SIZE || _height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Texture size too large");
    }
    glRenderbufferStorage(GL_RENDERBUFFER, _format, _width, _height);
    GLNGINE_CHECK_GL;
}

void RenderBuffer::allocateMultisample(int _width, int _height, RENDERBUFFER_FORMAT _format, int _sample) const
{
    if(_width > s_MAX_SIZE || _height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Texture size too large");
    }
    if(_sample > s_MAX_SAMPLE)
    {
        GLNGINE_EXCEPTION("Sample value too large");
    }
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, _sample, _format, _width, _height);
    GLNGINE_CHECK_GL;
}

void RenderBuffer::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add)
    {
        s_cache = add;
        glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    }
#else
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
#endif
}

void RenderBuffer::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_cache != add)
    {
        s_cache = add;
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
#else
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
#endif
}

RenderBuffer::Initializer::Initializer()
{
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &s_MAX_SIZE);
    glGetIntegerv(GL_MAX_SAMPLES, &s_MAX_SAMPLE);
}

}

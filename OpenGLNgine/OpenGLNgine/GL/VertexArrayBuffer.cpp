#include "OpenGLNgine/GL/VertexArrayBuffer.hpp"

using namespace std;

namespace GL
{
VertexArrayBuffer::VertexArrayBuffer() :
    IBindable()
{
    glGenVertexArrays(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the vertex array buffer");
    }
}

VertexArrayBuffer::~VertexArrayBuffer()
{
    glDeleteVertexArrays(1, &m_id);
}


void VertexArrayBuffer::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || !m_isBinded)
    {
        s_cache = add;
        m_isBinded = true;
        glBindVertexArray(m_id);
    }
#else
    glBindVertexArray(m_id);
#endif
}

void VertexArrayBuffer::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    static ptrdiff_t s_cache = reinterpret_cast< ptrdiff_t >(nullptr);
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_isBinded)
    {
        s_cache = add;
        m_isBinded = false;
        glBindVertexArray(0);
    }
#else
    glBindVertexArray(0);
#endif
}

}

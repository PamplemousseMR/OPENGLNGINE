#pragma once

#include "OpenGLNgine/GL/IBindable.hpp"
#include "OpenGLNgine/Core/Exception.hpp"

namespace GL
{

class VertexArrayBuffer final : public IBindable
{

public:

    VertexArrayBuffer();

    ~VertexArrayBuffer() override;

    VertexArrayBuffer(const VertexArrayBuffer&) = delete;

    VertexArrayBuffer(VertexArrayBuffer&&) = delete;

    VertexArrayBuffer& operator=(const VertexArrayBuffer&) = delete;

    VertexArrayBuffer& operator=(VertexArrayBuffer&&) = delete;

    inline void bind() const override;

    inline void unbind() const override;

private:

#ifdef GLNGINE_USE_STATE_CACHE
    /// Defines the bind status.
    mutable bool m_isBinded { false };
#endif

};

inline void VertexArrayBuffer::bind() const
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

inline void VertexArrayBuffer::unbind() const
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


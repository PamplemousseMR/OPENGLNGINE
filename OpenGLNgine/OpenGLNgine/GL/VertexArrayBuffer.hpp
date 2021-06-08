#pragma once

#include "OpenGLNgine/GL/IBindable.hpp"

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

    void bind() const override;

    void unbind() const override;

private:

#ifdef GLNGINE_USE_STATE_CACHE
    static ptrdiff_t s_cache;
#endif

};

}


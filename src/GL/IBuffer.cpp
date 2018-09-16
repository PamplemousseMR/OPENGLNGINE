#include "GL/IBuffer.hpp"

namespace GL
{
    IBuffer::IBuffer()
    {
    }

    IBuffer::~IBuffer() noexcept
    {
    }

    IBuffer::IBuffer(const IBuffer&)
    {
    }

    IBuffer::IBuffer(IBuffer&&)
    {
    }

    IBuffer& IBuffer::operator=(const IBuffer&)
    {
        return *this;
    }

    IBuffer& IBuffer::operator=(IBuffer&&)
    {
        return *this;
    }
}

#include "Hardware/IHardwareBuffer.hpp"
#include "Hardware/HardwareBufferManager.hpp"

#include <cassert>
#include <stdexcept>

using namespace std;

namespace Hardware
{

IHardwareBuffer::IHardwareBuffer(HardwareBufferManager* const _manager, GLenum _target, size_t _sizeInBytes, USAGE _usage):
    m_manager(_manager),
    m_target(_target),
    m_sizeInBytes(_sizeInBytes),
    m_usage(_usage)
{
    assert(_manager && "The buffer manager can't be nullptr");

    glGenBuffers(1, &m_id);
    assert(glGetError() == GL_NO_ERROR);
    if(m_id == 0)
    {
        throw overflow_error("[IHardwareBuffer] Out of memory");
    }

    glBindBuffer(m_target, m_id);
    glBufferData(m_target, m_sizeInBytes, nullptr, m_usage);
    assert(glGetError() == GL_NO_ERROR);
}

IHardwareBuffer::~IHardwareBuffer()
{
    glDeleteBuffers(1, &m_id);
    assert(glGetError() == GL_NO_ERROR);
}

void IHardwareBuffer::lock()
{
    glBindBuffer(m_target, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

void IHardwareBuffer::unlock()
{
    glBindBuffer(m_target, 0);
    assert(glGetError() == GL_NO_ERROR);
}

void IHardwareBuffer::readData(size_t _offset, size_t _sizeInBytes, void* _dest)
{
    glBindBuffer(m_target, m_id);
    glGetBufferSubData(m_target, _offset, _sizeInBytes, _dest);
    assert(glGetError() == GL_NO_ERROR);
}

void IHardwareBuffer::writeData(size_t _offset, size_t _sizeInBytes, const void* _src, bool _discard)
{
    glBindBuffer(m_target, m_id);
    if(_offset == 0 && _sizeInBytes == m_sizeInBytes)
    {
        glBufferData(m_target, m_sizeInBytes, _src, m_usage);
        assert(glGetError() == GL_NO_ERROR);
    }
    else
    {
        if(_discard)
        {
            glBufferData(m_target, m_sizeInBytes, nullptr, m_usage);
            assert(glGetError() == GL_NO_ERROR);
        }

        glBufferSubData(m_target, _offset, _sizeInBytes, _src);
        assert(glGetError() == GL_NO_ERROR);
    }
}

void IHardwareBuffer::copyData(const IHardwareBuffer& _src, size_t _srcOffset, size_t _dstOffset, size_t _sizeInBytes, bool _discard)
{
    if(_discard)
    {
        glBindBuffer(m_target, m_id);
        glBufferData(m_target, m_sizeInBytes, nullptr, m_usage);
        assert(glGetError() == GL_NO_ERROR);
    }

    glBindBuffer(GL_COPY_READ_BUFFER, _src.m_id);
    glBindBuffer(GL_COPY_WRITE_BUFFER, m_id);

    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, _srcOffset, _dstOffset, _sizeInBytes);
    assert(glGetError() == GL_NO_ERROR);

    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

}

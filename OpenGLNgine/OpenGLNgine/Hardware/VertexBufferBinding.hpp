#pragma once

#include "OpenGLNgine/Hardware/HardwareVertexBuffer.hpp"

#include <map>

namespace Hardware
{

class VertexData;

class VertexBufferBinding final
{

    friend VertexData;

public:

    typedef std::map<unsigned short, HardwareVertexBufferPtr> VertexBufferBindingMap;

    VertexBufferBinding(const VertexBufferBinding&) = delete;

    VertexBufferBinding(VertexBufferBinding&&) = delete;

    VertexBufferBinding& operator=(const VertexBufferBinding&) = delete;

    VertexBufferBinding& operator=(VertexBufferBinding&&) = delete;

    inline void setBinding(unsigned short _index, const HardwareVertexBufferPtr& _buffer);

    const HardwareVertexBufferPtr& getBuffer(unsigned short _index) const;

    inline const VertexBufferBindingMap& getBufferBindings() const;

private:

    VertexBufferBinding();

    ~VertexBufferBinding();

    VertexBufferBindingMap m_bindingMap {};

};

inline void VertexBufferBinding::setBinding(unsigned short _index, const HardwareVertexBufferPtr& _buffer)
{
    m_bindingMap[_index] = _buffer;
}

inline const VertexBufferBinding::VertexBufferBindingMap& VertexBufferBinding::getBufferBindings() const
{
    return m_bindingMap;
}

}

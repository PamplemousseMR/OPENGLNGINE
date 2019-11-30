#pragma once

#include "Hardware/HardwareVertexBuffer.hpp"

#include <map>

namespace Hardware
{

class VertexBufferBinding
{

public:

    typedef std::map<unsigned short, HardwareVertexBufferPtr> VertexBufferBindingMap;

    VertexBufferBinding();
    ~VertexBufferBinding();

    void setBinding(unsigned short, const HardwareVertexBufferPtr&);
    void unsetBinding(unsigned short);
    void unsetAllBindings();

    inline const VertexBufferBindingMap& getBindings() const;
    const HardwareVertexBufferPtr& getBuffer(unsigned short) const;

    inline bool isBufferBound(unsigned short) const;
    inline size_t getBufferCount() const;
    inline unsigned short getLastBoundIndex() const;

private:

    VertexBufferBinding(const VertexBufferBinding&) = delete;
    VertexBufferBinding(VertexBufferBinding&&) = delete;
    VertexBufferBinding& operator=(const VertexBufferBinding&) = delete;
    VertexBufferBinding& operator=(VertexBufferBinding&&) = delete;

    VertexBufferBindingMap m_bindingMap;

};

const VertexBufferBinding::VertexBufferBindingMap& VertexBufferBinding::VertexBufferBinding::getBindings() const
{
    return m_bindingMap;
}

bool VertexBufferBinding::isBufferBound(unsigned short _index) const
{
    return m_bindingMap.find(_index) != m_bindingMap.end();
}

size_t VertexBufferBinding::getBufferCount() const
{
    return m_bindingMap.size();
}

unsigned short VertexBufferBinding::getLastBoundIndex() const
{
    return m_bindingMap.empty() ? 0 : m_bindingMap.rbegin()->first;
}

}

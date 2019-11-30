#include "Hardware/VertexBufferBinding.hpp"

#include <algorithm>
#include <stdexcept>

using namespace std;

namespace Hardware
{

VertexBufferBinding::VertexBufferBinding()
{
}

VertexBufferBinding::~VertexBufferBinding()
{
    m_bindingMap.clear();
}

void VertexBufferBinding::setBinding(unsigned short _index, const HardwareVertexBufferPtr& _buffer)
{
    m_bindingMap[_index] = _buffer;
}

void VertexBufferBinding::unsetBinding(unsigned short _index)
{
    const VertexBufferBindingMap::const_iterator it = m_bindingMap.find(_index);
    if(it == m_bindingMap.end())
    {
        throw invalid_argument("[VertexBufferBinding] A vertex buffer with this index doesn't exist");
    }
    m_bindingMap.erase(it);
}

void VertexBufferBinding::unsetAllBindings()
{
    m_bindingMap.clear();
}

const HardwareVertexBufferPtr& VertexBufferBinding::getBuffer(unsigned short _index) const
{
    const VertexBufferBindingMap::const_iterator it = m_bindingMap.find(_index);
    if(it == m_bindingMap.end())
    {
        throw invalid_argument("[VertexBufferBinding] A vertex buffer with this index doesn't exist");
    }
    return it->second;
}

}

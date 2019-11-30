#pragma once

#include "Hardware/IHardwareBuffer.hpp"
#include "Hardware/HardwareIndexBuffer.hpp"
#include "Hardware/HardwareVertexBuffer.hpp"
#include "Hardware/VertexDeclaration.hpp"
#include "Hardware/VertexBufferBinding.hpp"

#include <set>

namespace Hardware
{

class HardwareBufferManager final
{

public:

    typedef std::set<HardwareIndexBuffer*> IndexBufferList;
    typedef std::set<HardwareVertexBuffer*> VertexBufferList;

    typedef std::set<VertexDeclaration*> VertexDeclarationList;
    typedef std::set<VertexBufferBinding*> VertexBufferBindingList;

    static HardwareBufferManager& getInstance();
    static HardwareBufferManager* getInstancePtr();

    HardwareIndexBufferPtr createIndexBuffer(HardwareIndexBuffer::INDEX_TYPE, size_t, IHardwareBuffer::HARDWAREBUFFER_USAGE);
    HardwareVertexBufferPtr createVertexBuffer(size_t, size_t, IHardwareBuffer::HARDWAREBUFFER_USAGE);

    VertexBufferBinding* createVertexBufferBinding();
    VertexDeclaration* createVertexDeclaration();

    void destroyVertexBufferBinding(VertexBufferBinding*);
    void destroyVertexDeclaration(VertexDeclaration*);

    void destroyAllVertexBufferBinding();
    void destroyAllVertexDeclaration();

    void _notifyIndexBufferDestroyed(HardwareIndexBuffer*);
    void _notifyVertexBufferDestroyed(HardwareVertexBuffer*);

private:

    class MemGuard final
    {

    public:

        ~MemGuard()
        {
            delete HardwareBufferManager::s_INSTANCE;
            HardwareBufferManager::s_INSTANCE = nullptr;
        }

    };

    static HardwareBufferManager* s_INSTANCE;

    HardwareBufferManager();
    ~HardwareBufferManager();

    HardwareBufferManager(const HardwareBufferManager&) = delete;
    HardwareBufferManager(HardwareBufferManager&&) = delete;
    HardwareBufferManager& operator=(const HardwareBufferManager&) = delete;
    HardwareBufferManager& operator=(HardwareBufferManager&&) = delete;

    IndexBufferList m_indexBuffers;
    VertexBufferList m_vertexBuffers;

    VertexDeclarationList m_vertexDeclarations;
    VertexBufferBindingList m_vertexBufferBindings;
};

}

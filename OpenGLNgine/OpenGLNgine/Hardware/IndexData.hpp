#pragma once

#include "OpenGLNgine/Hardware/HardwareIndexBuffer.hpp"

namespace Hardware
{

class HardwareBufferManager;

class IndexData final
{

    friend HardwareBufferManager;

public:

    IndexData(const IndexData&) = delete;

    IndexData(IndexData&&) = delete;

    IndexData& operator=(const IndexData&) = delete;

    IndexData& operator=(IndexData&&) = delete;

    HardwareIndexBufferPtr m_indexBuffer { nullptr };

    int m_indexStart {0};

    int m_indexCount {0};

private:

    IndexData();

    ~IndexData();

};

}

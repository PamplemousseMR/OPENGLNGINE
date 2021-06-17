#include "OpenGLNgine/Core/IHardwareResource.hpp"
#include "OpenGLNgine/Core/Exception.hpp"

#include <sstream>

namespace Core
{

IHardwareResource::IHardwareResource(const IHardwareManager* const _manager, const std::string& _name) :
    IResource(_name),
    m_manager(_manager)
{
    GLNGINE_ASSERT_IF(!_manager, "The manager shall not be nullptr");
}

IHardwareResource::~IHardwareResource()
{
}

}

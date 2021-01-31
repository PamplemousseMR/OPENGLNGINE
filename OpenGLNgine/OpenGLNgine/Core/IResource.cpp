#include "OpenGLNgine/Core/IResource.hpp"
#include "OpenGLNgine/Core/Exception.hpp"

#include <sstream>

namespace Core
{

IResource::IResource()
{
    std::ostringstream address;
    address << (const void*)this;
    m_name = address.str();
}

IResource::IResource(const std::string& _name):
    m_name(_name)
{
    GLNGINE_ASSERT_IF(_name.empty(), "The name of a nameable object can't be empty");
}

IResource::~IResource()
{
}

}

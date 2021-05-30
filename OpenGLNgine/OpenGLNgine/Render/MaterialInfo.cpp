#include "OpenGLNgine/Render/MaterialInfo.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/SceneManager.hpp"

namespace Render
{

MaterialInfo::MaterialInfo(const std::string& _name):
    ::Core::IResource(_name)
{
}

MaterialInfo::~MaterialInfo()
{
}

}

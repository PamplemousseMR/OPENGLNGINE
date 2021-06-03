#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include "OpenGLNgine/Hardware/Pass.hpp"

#include <memory>
#include <vector>

namespace Hardware
{

class RenderTarget;
class RenderTargetManager;

typedef std::shared_ptr< RenderTarget > RenderTargetPtr;

class RenderTarget final : public ::Core::IResource
{

public:

    RenderTarget(RenderTargetManager* const _manager, const std::string& _name);

    ~RenderTarget();

    RenderTarget(const RenderTarget&) = delete;

    RenderTarget(RenderTarget&&) = delete;

    RenderTarget& operator=(const RenderTarget&) = delete;

    RenderTarget& operator=(RenderTarget&&) = delete;

private:

    RenderTargetManager* const m_manager;

};

}

#pragma once

#include "OpenGLNgine/Core/IResource.hpp"

#include "OpenGLNgine/Hardware/Pass.hpp"

#include <memory>
#include <vector>

namespace Hardware
{

class Material;
class MaterialManager;

typedef std::shared_ptr< Material > MaterialPtr;

class Material final : public ::Core::IResource
{

    friend MaterialManager;

public:

    typedef std::vector< Pass* > PassList;

    ~Material();

    Material(const Material&) = delete;

    Material(Material&&) = delete;

    Material& operator=(const Material&) = delete;

    Material& operator=(Material&&) = delete;

    Pass* createPass();

    void destroyAllPasses();

    inline const PassList& getPasses() const;

private:

    Material(MaterialManager* const _manager, const std::string& _name);

    MaterialManager* const m_manager;

    PassList m_passes {};

};

inline const Material::PassList& Material::getPasses() const
{
    return m_passes;
}

}

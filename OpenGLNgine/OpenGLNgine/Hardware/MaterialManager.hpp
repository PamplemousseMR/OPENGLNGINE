#pragma once

#include "OpenGLNgine/Core/IManager.hpp"
#include "OpenGLNgine/Hardware/Material.hpp"

namespace Hardware
{

class MaterialManager final : public ::Core::IManager< Material >
{

public:

    static MaterialManager& getInstance();

    MaterialManager(const MaterialManager&) = delete;

    MaterialManager(MaterialManager&&) = delete;

    MaterialManager& operator=(const MaterialManager&) = delete;

    MaterialManager& operator=(MaterialManager&&) = delete;

    MaterialPtr create(const std::string& _name);

    void destroy(const MaterialPtr& _material);

private:

    struct Initializer final
    {
        Initializer();

        ~Initializer();
    };

    static MaterialManager* s_instance;

    MaterialManager();

    ~MaterialManager();

};

}

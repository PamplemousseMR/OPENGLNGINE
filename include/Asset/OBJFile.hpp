#pragma once

#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace Assets
{
class Material;
class Object;

class OBJFile
{

public:

    OBJFile() noexcept;
    ~OBJFile() noexcept;

    void load(const std::filesystem::path&);

    const std::vector<Object*>& getObjects() const noexcept;
    long long getLoadTime() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    std::vector<std::string> split(const std::string & str, char splitter) const noexcept;
    std::vector<std::string> removeNullptr(const std::vector<std::string> & str) const noexcept;
    void push(std::vector<glm::vec3>*, std::vector<glm::vec3>*, std::vector<glm::vec2>*, std::vector<glm::vec3>*, std::string*) const;
    std::vector<Material*> findMaterial(const std::string&) const noexcept;
    void loadMTLFile(const std::filesystem::path&) const;

private:

    std::vector<Object*> m_objects;
    std::string m_name;
    long long m_loadTime;

};

std::ostream& operator<<(std::ostream& o, const OBJFile&) noexcept;

}


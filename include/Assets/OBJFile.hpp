#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

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
    OBJFile(const OBJFile&);
    OBJFile(OBJFile&&);
    OBJFile& operator=(const OBJFile&);
    OBJFile& operator=(OBJFile&&);

    void load(const std::filesystem::path&);

    const std::vector<Object*>& getObjects() const noexcept;

    std::ostream& print(std::ostream&) const noexcept;

private:

    static std::vector<std::string> split(const std::string & str, char splitter) noexcept;
    static std::vector<std::string> removeNullptr(const std::vector<std::string> & str) noexcept;
    static void checkSize(const std::vector<std::string>&, size_t, size_t, int);

private:

    void push(std::vector<glm::vec3>*, std::vector<glm::vec3>*, std::vector<glm::vec2>*, std::vector<glm::vec3>*, std::string*) const;
    std::vector<Material*> findMaterial(const std::string&) const noexcept;
    void loadMTLFile(const std::filesystem::path&) const;

private:

    std::vector<Object*> m_objects{};
    std::string m_name {};

};

std::ostream& operator<<(std::ostream& o, const OBJFile&) noexcept;

}


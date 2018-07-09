#pragma once

#include <glm/glm.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Assets
{
class Material;
class Object;

class OBJFile
{

public:

    OBJFile();
    ~OBJFile();

    void load(const std::string&) throw();

    const std::vector<Object*>& getObjects() const;
    long long getLoadTime() const;

    std::ostream& print(std::ostream&) const;

private:

    std::vector<std::string> split(const std::string & str, char splitter) const;
    std::vector<std::string> removenullptr(const std::vector<std::string> & str) const;
    void push(std::vector<glm::vec3>*, std::vector<glm::vec3>*, std::vector<glm::vec2>*, std::vector<glm::vec3>*, std::string*) const throw();
    std::vector<Material*> findMaterial(const std::string&) const;
    void loadMTLFile(const std::string&) const throw();

private:

    std::vector<Object*> m_objects;
    std::string m_name;
    long long m_loadTime;

};

std::ostream& operator<<(std::ostream& o, const OBJFile&);

}


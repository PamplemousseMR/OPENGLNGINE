#pragma once

#include <GL\glew.h>

#include <iostream>
#include <string>
#include <vector>

namespace GL
{

enum textureType
{
    TEXTURE_1D = GL_TEXTURE_1D,
    TEXTURE_2D = GL_TEXTURE_2D,
};

class Texture
{

public:

    Texture(textureType);
    ~Texture();

    int load(const char*) throw(...);
    void generateMipmap() const;
    void bind() throw(...);
    void unbind();

    GLuint getId() const;
    int getLocation() const;
    textureType getType() const;
    const std::string& getName() const;

    void setParameter(GLenum, GLint) const;

private:

    static std::vector<bool> s_location;
    static bool s_first;

private:

    textureType m_type;
    std::string m_name;
    bool m_hasAlpha;
    GLuint m_id;
    int m_location;


};

}


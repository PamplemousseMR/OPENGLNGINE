#include "GL/Texture.hpp"

#include "SOIL/SOIL.h"

#include <algorithm>

using namespace std;

namespace GL
{
    vector<bool> Texture::s_location;
    bool Texture::s_first = false;

    Texture::Texture(textureType type)
        : m_type(type), m_location(-1), m_hasAlpha(false)
    {
#ifdef _DEBUG
        cout << "[Texture " <<m_name << "] [Texture(textureType type)]..." << endl;
#endif
        if (!s_first)
        {
            GLint size;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);
            for (int i(0); i < size; i++)
                s_location.push_back(false);
            s_first = true;
        }
        glGenTextures(1, &m_id);
#ifdef _DEBUG
        cout << "[Texture " << m_name << "] [Texture(textureType type)]...\tsuccess" << endl;
#endif
    }


    Texture::~Texture()
    {
#ifdef _DEBUG
        cout << "[Texture " << m_name << "] [~Texture()]..." << endl;
#endif
        glDeleteTextures(1, &m_id);
#ifdef _DEBUG
        cout << "[Texture " << m_name << "] [~Texture()]...\tsuccess" << endl;
#endif
    }

    GLuint Texture::getId() const
    {
        return m_id;
    }

    int Texture::getLocation() const
    {
        return m_location;
    }

    textureType Texture::getType() const
    {
        return m_type;
    }

    const string& Texture::getName() const
    {
        return m_name;
    }

    int Texture::load(const char* imagepath) throw()
    {
        m_name = imagepath;
#ifdef _DEBUG
        cout << "[Texture " << m_name << "] [load(const char* imagepath) throw()]..." << endl;
#endif
        FILE * file;
        file = fopen(imagepath, "rb");
        string name = imagepath;
        if (!file)
            throw invalid_argument("[Texture " + m_name + "] [load(const char* imagepath) throw()] can't open file : " + name);

        string path = imagepath;
        string fileFormat = "";
        for (int i((int)path.length() - 1); i > 0; i--)
        {
            if (path[i] == '.')
                break;
            else
                fileFormat.push_back(path[i]);
        }
        reverse(fileFormat.begin(), fileFormat.end());
        if (fileFormat == "bmp" || fileFormat == "jpg" || fileFormat == "jpeg")
            m_hasAlpha = false;
        else if (fileFormat == "png" || fileFormat == "tga" || fileFormat == "psd" || fileFormat == "DDS")
            m_hasAlpha = true;
        else if (fileFormat == "hdr")
            throw invalid_argument("[Texture " + m_name + "] [load(const char* imagepath) throw()] TODO HDR");
        else
            throw invalid_argument("[Texture " + m_name + "] [load(const char* imagepath) throw()] can't load : " + fileFormat + " file");
        int width, height, chanel;
        unsigned char* data;
        int soilFormat = SOIL_LOAD_RGB;
        GLuint internalFormat = GL_RGB;
        GLenum format = GL_RGB;
        if (m_hasAlpha)
        {
            soilFormat = SOIL_LOAD_RGBA;
            internalFormat = GL_RGBA;
            format = GL_RGBA;
        }
        data = SOIL_load_image(imagepath, &width, &height, &chanel, soilFormat);
        switch (m_type)
        {
            case TEXTURE_1D :
                if (height != 0)
                    throw invalid_argument("[Texture " + m_name + "] [load(const char* imagepath) throw()] not a 1D texture");
                glTexImage1D(m_type, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, data);
            break;
            case TEXTURE_2D :
                glTexImage2D(m_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            break;
        }
        SOIL_free_image_data(data);
#ifdef _DEBUG
        cout << "[Texture " << m_name << "] [load(const char* imagepath) throw()]...\tsuccess" << endl;
#endif
        return width;
    }


    void Texture::setParameter(GLenum pname, GLint param) const
    {
        glTexParameteri(m_type, pname, param);
    }

    void Texture::generateMipmap() const
    {
        glGenerateMipmap(m_type);
    }

    void Texture::bind() throw()
    {
        for (int i(0); i < s_location.size(); i++)
            if (s_location[i] == false)
            {
                m_location = i;
                s_location[i] = true;
                break;
            }
        if (m_location == -1)
            throw invalid_argument("[Texture " + m_name + "] [bind() throw()] too much bind texture");
        glActiveTexture(GL_TEXTURE0 + m_location);
        glBindTexture(m_type, m_id);
    }

    void Texture::unbind()
    {
        s_location[m_location] = false;
        m_location = -1;
        glBindTexture(m_type, 0);
    }

}

#include "GL/Texture.hpp"

#include "SOIL/SOIL.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace GL
{
    vector<bool> Texture::s_location;
    bool Texture::s_first = false;

    Texture::Texture(TEXTURE_TYPE type) :
        m_type(type)
    {
        if (!s_first)
        {
            GLint size;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);
            for (int i(0); i < size; ++i)
            {
                s_location.push_back(false);
            }
            s_first = true;
        }
        for (size_t i=0 ; i<s_location.size() ; ++i)
        {
            if (s_location[i] == false)
            {
                m_location = int(i);
                s_location[i] = true;
                break;
            }
        }
        if (m_location == -1)
        {
            throw overflow_error("[Texture] Too much active texture");
        }
        glGenTextures(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[Texture] Out of memory");
        }
    }


    Texture::~Texture() noexcept
    {
        glDeleteTextures(1, &m_id);
        s_location[size_t(m_location)] = false;
    }

    int Texture::load(const std::filesystem::path& _path)
    {
        if(!filesystem::exists(_path) || !filesystem::is_regular_file(_path))
        {
            throw invalid_argument("[Texture] path doesn't exists : " + _path.string());
        }

        const string fileFormat = _path.extension().string();
        if (fileFormat == ".bmp" || fileFormat == ".jpg" || fileFormat == ".jpeg")
        {
            m_hasAlpha = false;
        }
        else if (fileFormat == ".png" || fileFormat == ".tga" || fileFormat == ".psd" || fileFormat == ".DDS")
        {
            m_hasAlpha = true;
        }
        else if (fileFormat == ".hdr")
        {
            throw invalid_argument("[Texture] TODO HDR");
        }
        else
        {
            throw invalid_argument("[Texture] can't load : " + fileFormat + " file");
        }

        int width, height, chanel;
        unsigned char* data;
        int soilFormat = SOIL_LOAD_RGB;
        GLint internalFormat = GL_RGB;
        GLenum format = GL_RGB;
        if (m_hasAlpha)
        {
            soilFormat = SOIL_LOAD_RGBA;
            internalFormat = GL_RGBA;
            format = GL_RGBA;
        }
        data = SOIL_load_image(_path.string().c_str(), &width, &height, &chanel, soilFormat);
        switch (m_type)
        {
            case TEXTURE_1D :
                if (height != 0)
                {
                    throw overflow_error("[Texture] not a 1D texture");
                }
                glTexImage1D(m_type, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, data);
            break;
            case TEXTURE_2D :
                glTexImage2D(m_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            break;
        }
        SOIL_free_image_data(data);
        return width;
    }

    void Texture::bind()
    {
        glActiveTexture(GLenum(GL_TEXTURE0 + m_location));
        glBindTexture(m_type, m_id);
    }

    void Texture::unbind() noexcept
    {
        glBindTexture(m_type, 0);
    }

}

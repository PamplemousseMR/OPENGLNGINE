#include "GL/Texture.hpp"

#include "SOIL/SOIL.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace GL
{
    vector<bool> Texture::s_location;
    int Texture::s_maxSize;
    bool Texture::s_first = false;

    Texture::Texture(TEXTURE_TYPE type) :
        IGLObject(),
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
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
            s_maxSize = size;
        }
        for(size_t i=0 ; i<s_location.size() ; ++i)
        {
            if (s_location[i] == false)
            {
                m_location = int(i);
                s_location[i] = true;
                break;
            }
        }
        if(m_location == -1)
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

    Texture::Texture(const Texture& _texture) :
        IGLObject(_texture),
        m_type(_texture.m_type)
    {
        for(size_t i=0 ; i<s_location.size() ; ++i)
        {
            if (s_location[i] == false)
            {
                m_location = int(i);
                s_location[i] = true;
                break;
            }
        }
        if(m_location == -1)
        {
            throw overflow_error("[Texture] Too much active texture");
        }
        glGenTextures(1, &m_id);
        if(m_id == 0)
        {
            throw overflow_error("[Texture] Out of memory");
        }

        _texture.bind();

        GLint width;
        GLint height;
        GLint internalFormat;
        glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_COMPONENTS, &internalFormat);
        glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_HEIGHT, &height);

        size_t numBytes;
        GLenum format;
        switch(internalFormat)
        {
        case GL_RGB:
            numBytes = size_t(width * height * 3);
            format = GL_RGB;
            break;
        case GL_RGBA:
            numBytes = size_t(width * height * 4);
            format = GL_RGBA;
            break;
        default:
            throw invalid_argument("[Texture] Unsuported format");
            break;
        }

        if(numBytes > 0)
        {
            std::vector< unsigned char > data(numBytes);
            glGetTexImage(m_type, 0, format, GL_UNSIGNED_BYTE, &data[0]);

            _texture.unbind();

            bind();
            switch (m_type)
            {
                case TEXTURE_1D :
                    glTexImage1D(m_type, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                break;
                case TEXTURE_2D :
                    glTexImage2D(m_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                break;
            }
            unbind();
        }
        else
        {
            _texture.unbind();
        }
    }

    Texture& Texture::operator=(const Texture& _texture)
    {
        if(this != &_texture)
        {
            IGLObject::operator=(_texture);
            m_type = _texture.m_type;

            GLint width;
            GLint height;
            GLint internalFormat;
            size_t numBytes;
            GLenum format;

            _texture.bind();

            glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_COMPONENTS, &internalFormat);
            glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(m_type, 0, GL_TEXTURE_HEIGHT, &height);

            switch(internalFormat)
            {
            case GL_RGB:
                numBytes = size_t(width * height * 3);
                format = GL_RGB;
                break;
            case GL_RGBA:
                numBytes = size_t(width * height * 4);
                format = GL_RGBA;
                break;
            default:
                throw invalid_argument("[Texture] Unsuported format");
                break;
            }

            if(numBytes > 0)
            {
                std::vector< unsigned char > data(numBytes);
                glGetTexImage(m_type, 0, format, GL_UNSIGNED_BYTE, &data[0]);

                _texture.unbind();

                bind();
                switch (m_type)
                {
                    case TEXTURE_1D :
                        glTexImage1D(m_type, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                    break;
                    case TEXTURE_2D :
                        glTexImage2D(m_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                    break;
                }
                unbind();
            }
            else
            {
                _texture.unbind();
            }
        }
        return *this;
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
        if(width > s_maxSize || height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        switch (m_type)
        {
            case TEXTURE_1D :
                if (height != 0)
                {
                    throw runtime_error("[Texture] not a 1D texture");
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

    void Texture::loadRGBA(int _width, int _height)
    {
        if(_width > s_maxSize || _height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        switch (m_type)
        {
            case TEXTURE_1D :
                if (_height != 0)
                {
                    throw runtime_error("[Texture] Not a 1D texture");
                }
                glTexImage1D(m_type, 0, GL_RGBA, _width, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            break;
            case TEXTURE_2D :
                glTexImage2D(m_type, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            break;
        }
    }

}

#include "GL/Texture.hpp"

#include "SOIL/SOIL.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

namespace GL
{
    vector<bool> Texture::s_location;
    GLint Texture::s_maxSize;
    bool Texture::s_first = false;

    Texture::Texture(TEXTURE_TYPE type) :
        IGLObject(),
        m_type(type)
    {
        if(!s_first)
        {
            s_first = true;
            GLint size;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);
            for (int i(0); i < size; ++i)
            {
                s_location.push_back(false);
            }
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &s_maxSize);
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
        assert(glGetError() == GL_NO_ERROR);
        if(m_id == 0)
        {
            throw overflow_error("[Texture] Out of memory");
        }
        switch(m_type)
        {
            case TYPE_1D :
                m_glType = GL_TEXTURE_1D;
            break;
            case TYPE_2D :
            case TYPE_DEPTH :
                m_glType = GL_TEXTURE_2D;
            break;
        }
    }

    Texture::~Texture() noexcept
    {
        glDeleteTextures(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        s_location[size_t(m_location)] = false;
    }

    Texture::Texture(const Texture& _texture) :
        IGLObject(_texture),
        m_type(_texture.m_type),
        m_glType(_texture.m_glType)
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
        glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_COMPONENTS, &internalFormat);
        glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_HEIGHT, &height);

        GLenum format;
        size_t numBytes;
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
        case GL_DEPTH_COMPONENT:
            numBytes = size_t(width * height);
            format = GL_DEPTH_COMPONENT;
            break;
        default:
            throw invalid_argument("[Texture] Unsuported format");
            break;
        }

        if(numBytes > 0)
        {
            switch(m_type)
            {
                case TYPE_1D :
                    {
                        std::vector< unsigned char > data(numBytes);
                        glGetTexImage(GL_TEXTURE_1D, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                        _texture.unbind();
                        bind();
                        glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                    }
                break;
                case TYPE_2D :
                    {
                        std::vector< unsigned char > data(numBytes);
                        glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                        _texture.unbind();
                        bind();
                        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                    }
                break;
                case TYPE_DEPTH :
                    {
                        std::vector< float > data(numBytes);
                        glGetTexImage(GL_TEXTURE_2D, 0, format, GL_FLOAT, &data[0]);
                        _texture.unbind();
                        bind();
                        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, &data[0]);
                    }
                break;
            }
            unbind();
        }
        else
        {
            _texture.unbind();
        }
        assert(glGetError() == GL_NO_ERROR);
    }

    Texture& Texture::operator=(const Texture& _texture)
    {
        if(this != &_texture)
        {
            IGLObject::operator=(_texture);
            m_type = _texture.m_type;
            m_glType = _texture.m_glType;

            GLint width;
            GLint height;
            GLint internalFormat;
            size_t numBytes;
            GLenum format;

            _texture.bind();

            glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_COMPONENTS, &internalFormat);
            glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(m_glType, 0, GL_TEXTURE_HEIGHT, &height);

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
            case GL_DEPTH_COMPONENT:
                numBytes = size_t(width * height);
                format = GL_DEPTH_COMPONENT;
                break;
            default:
                throw invalid_argument("[Texture] Unsuported format");
                break;
            }

            if(numBytes > 0)
            {
                switch(m_type)
                {
                    case TYPE_1D :
                        {
                            std::vector< unsigned char > data(numBytes);
                            glGetTexImage(GL_TEXTURE_1D, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                            _texture.unbind();
                            bind();
                            glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                        }
                    break;
                    case TYPE_2D :
                        {
                            std::vector< unsigned char > data(numBytes);
                            glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                            _texture.unbind();
                            bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, &data[0]);
                        }
                    break;
                    case TYPE_DEPTH :
                        {
                            std::vector< float > data(numBytes);
                            glGetTexImage(GL_TEXTURE_2D, 0, format, GL_FLOAT, &data[0]);
                            _texture.unbind();
                            bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, &data[0]);
                        }
                    break;
                }
                unbind();
            }
            else
            {
                _texture.unbind();
            }
            assert(glGetError() == GL_NO_ERROR);
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
        GLint destFormat = GL_RGB;
        GLenum srcFormat = GL_RGB;
        if (m_hasAlpha)
        {
            soilFormat = SOIL_LOAD_RGBA;
            destFormat = GL_RGBA;
            srcFormat = GL_RGBA;
        }
        data = SOIL_load_image(_path.string().c_str(), &width, &height, &chanel, soilFormat);
        if(width > s_maxSize || height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        switch(m_type)
        {
            case TYPE_1D :
                if (height != 1)
                {
                    throw runtime_error("[Texture] not a 1D texture");
                }
                glTexImage1D(GL_TEXTURE_1D, 0, destFormat, width, 0, srcFormat, GL_UNSIGNED_BYTE, data);
            break;
            case TYPE_2D :
                glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height, 0, srcFormat, GL_UNSIGNED_BYTE, data);
            break;
            case TYPE_DEPTH:
                throw invalid_argument("[Texture] Unsuported format");
            break;
        }
        assert(glGetError() == GL_NO_ERROR);
        SOIL_free_image_data(data);
        return width;
    }

    void Texture::load(int _width, int _height, TEXTURE_FORMAT _format) const
    {
        if(_width > s_maxSize || _height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        switch (m_type)
        {
            case TYPE_1D :
                if (_height != 1)
                {
                    throw runtime_error("[Texture] Not a 1D texture");
                }
                glTexImage1D(GL_TEXTURE_1D, 0, _format, _width, 0, GLenum(_format), GL_UNSIGNED_BYTE, nullptr);
            break;
            case TYPE_2D :
                glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, GLenum(_format), GL_UNSIGNED_BYTE, nullptr);
            case TYPE_DEPTH :
                glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, GLenum(_format), GL_FLOAT, nullptr);
            break;
        }
        assert(glGetError() == GL_NO_ERROR);
    }

}

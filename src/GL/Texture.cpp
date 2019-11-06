#include "GL/Texture.hpp"

#include "SOIL/SOIL.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

namespace GL
{
    void Texture::genTexture()
    {
        for(size_t i=0 ; i<s_location.size() ; ++i)
        {
            if(s_location[i] == false)
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
    }

    vector<bool> Texture::s_location = {};
    GLint Texture::s_maxSize = 0;
    GLint Texture::s_maxSample = 0;
    bool Texture::s_first = true;

    Texture::Texture(TEXTURE_TYPE type) :
        IBindable(),
        m_type(type)
    {
        if(s_first)
        {
            s_first = false;
            GLint size;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);
            for(int i(0); i < size; ++i)
            {
                s_location.push_back(false);
            }
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &s_maxSize);
            glGetIntegerv(GL_MAX_SAMPLES, &s_maxSample);
        }
        genTexture();
    }

    Texture::~Texture() noexcept
    {
        glDeleteTextures(1, &m_id);
        assert(glGetError() == GL_NO_ERROR);
        s_location[size_t(m_location)] = false;
    }

    Texture::Texture(const Texture& _texture) :
        IBindable(_texture),
        m_type(_texture.m_type),
        m_format(_texture.m_format)
    {
        genTexture();

        _texture.bind();
        GLint width;
        GLint height;
        GLint depth;
        GLint destFormat;
        switch(m_type)
        {
            case TYPE_1D :
                glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
                glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
                glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_HEIGHT, &height);
                glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_DEPTH, &depth);
            break;
            case TYPE_2D :
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
            break;
            case TYPE_2DMULTISAMPLE :
                throw invalid_argument("[Texture] TODO");
        }

        size_t numBytes = size_t(width * height * depth) * 4;
        std::vector< unsigned char > data(numBytes);
        if(numBytes > 0)
        {
            switch(m_type)
            {
                case TYPE_1D :
                    {
                        glGetTexImage(GL_TEXTURE_1D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                        _texture.unbind();
                        bind();
                        glTexImage1D(GL_TEXTURE_1D, 0, destFormat, width, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                    }
                break;
                case TYPE_2D :
                    {
                        glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                        _texture.unbind();
                        bind();
                        glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                    }
                break;
                case TYPE_2DMULTISAMPLE :
                    throw invalid_argument("[Texture] TODO");
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
            IObject::operator=(_texture);
            m_type = _texture.m_type;
            m_format = _texture.m_format;

            _texture.bind();
            GLint width;
            GLint height;
            GLint depth;
            GLint destFormat;
            switch(m_type)
            {
                case TYPE_1D :
                    glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
                    glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
                    glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_HEIGHT, &height);
                    glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_DEPTH, &depth);
                break;
                case TYPE_2D :
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
                    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
                break;
                case TYPE_2DMULTISAMPLE :
                    throw invalid_argument("[Texture] TODO");
            }

            size_t numBytes = size_t(width * height * depth) * 4;
            std::vector< unsigned char > data(numBytes);
            if(numBytes > 0)
            {
                switch(m_type)
                {
                    case TYPE_1D :
                        {
                            glGetTexImage(GL_TEXTURE_1D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                            _texture.unbind();
                            bind();
                            glTexImage1D(GL_TEXTURE_1D, 0, destFormat, width, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                        }
                    break;
                    case TYPE_2D :
                        {
                            glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                            _texture.unbind();
                            bind();
                            glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                        }
                    break;
                    case TYPE_2DMULTISAMPLE :
                        throw invalid_argument("[Texture] TODO");
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

    int Texture::load(const std::filesystem::path& _path, TEXTURE_INTERNALFORMAT _internalFormat)
    {
        if(!filesystem::exists(_path) || !filesystem::is_regular_file(_path))
        {
            throw invalid_argument("[Texture] path doesn't exists : " + _path.string());
        }

        bool hasAlpha;
        const string fileFormat = _path.extension().string();
        if(fileFormat == ".bmp" || fileFormat == ".jpg" || fileFormat == ".jpeg")
        {
            hasAlpha = false;
        }
        else if(fileFormat == ".png" || fileFormat == ".tga" || fileFormat == ".psd" || fileFormat == ".DDS")
        {
            hasAlpha = true;
        }
        else if(fileFormat == ".hdr")
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
        m_format = FORMAT_RGB;
        if(hasAlpha)
        {
            soilFormat = SOIL_LOAD_RGBA;
            m_format = FORMAT_RGBA;
        }
        data = SOIL_load_image(_path.string().c_str(), &width, &height, &chanel, soilFormat);
        if(width > s_maxSize || height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        switch(m_type)
        {
            case TYPE_1D :
                if(height != 1)
                {
                    throw invalid_argument("[Texture] not a 1D texture");
                }
                glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, width, 0, m_format, GL_UNSIGNED_BYTE, data);
            break;
            case TYPE_2D :
                glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);
            break;
            case TYPE_2DMULTISAMPLE :
                throw std::invalid_argument("[Texture] Can't load image to multisampled textures");
        }
        assert(glGetError() == GL_NO_ERROR);
        SOIL_free_image_data(data);
        return width;
    }

    void Texture::allocate(int _width, int _height, TEXTURE_INTERNALFORMAT _internalFormat, TEXTURE_FORMAT _format, TEXTURE_DATA _data)
    {
        if(_width > s_maxSize || _height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        m_format = _format;
        switch (m_type)
        {
            case TYPE_1D :
                if(_height != 1)
                {
                    throw invalid_argument("[Texture] Not a 1D texture");
                }
                glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, _width, 0, _format, _data, nullptr);
            break;
            case TYPE_2D :
                glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _data, nullptr);
            break;
            case TYPE_2DMULTISAMPLE :
                throw std::invalid_argument("[Texture] Can't allocate multisampled textures without sample");
            break;
        }
        assert(glGetError() == GL_NO_ERROR);
    }

    void Texture::allocateMultisample(int _width, int _height, TEXTURE_INTERNALFORMAT _internalFormat, TEXTURE_FORMAT _format, int _sample)
    {
        if(_width > s_maxSize || _height > s_maxSize)
        {
            throw overflow_error("[Texture] Size too big");
        }
        if(_sample > s_maxSample)
        {
            throw overflow_error("[Texture] Sample too hight");
        }
        m_format = _format;
        switch (m_type)
        {
            case TYPE_1D :
            case TYPE_2D :
                throw std::invalid_argument("[Texture] Can't allocate multisample to no multisampled textures");
            break;
            case TYPE_2DMULTISAMPLE :
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _sample, GLenum(_internalFormat), _width, _height, GL_TRUE);
        }
        assert(glGetError() == GL_NO_ERROR);
    }

}

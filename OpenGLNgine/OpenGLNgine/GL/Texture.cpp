#include "OpenGLNgine/GL/Texture.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <SOIL2/SOIL2.h>

namespace GL
{

GLint Texture::s_MAX_SIZE = 0;
GLint Texture::s_MAX_SAMPLE = 0;
GLint Texture::s_MAX_LOCATION = 0;

Texture::Texture() :
    IBindable()
{
    const static Initializer s_INITIALIZER;
    glGenTextures(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the texture");
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

Texture::Texture(const Texture& _texture) :
    IBindable(_texture),
    m_type(_texture.m_type),
    m_format(_texture.m_format)
{
    glGenTextures(1, &m_id);
    if(m_id == 0)
    {
        GLNGINE_EXCEPTION("Can't create the texture");
    }

    _texture.bind();
    GLint width = 0;
    GLint height = 0;
    GLint depth = 0;
    GLint destFormat = 0;
    switch(m_type)
    {
    case TT_1D :
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_DEPTH, &depth);
        break;
    case TT_2D :
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
        break;
    case TT_2DMULTISAMPLE :
        GLNGINE_EXCEPTION("TODO");
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }

    size_t numBytes = size_t(width * height * depth) * 4;
    std::vector< unsigned char > data(numBytes);
    if(numBytes > 0)
    {
        switch(m_type)
        {
        case TT_1D :
        {
            glGetTexImage(GL_TEXTURE_1D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
            bind();
            glTexImage1D(GL_TEXTURE_1D, 0, destFormat, width, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
        }
            break;
        case TT_2D :
        {
            glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
            bind();
            glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
        }
            break;
        case TT_2DMULTISAMPLE :
            GLNGINE_EXCEPTION("TODO");
        default:
            GLNGINE_EXCEPTION("Unhandle texture type");
        }
        unbind();
    }
    GLNGINE_CHECK_GL;
}

Texture& Texture::operator=(const Texture& _texture)
{
    if(this != &_texture)
    {
        m_type = _texture.m_type;
        m_format = _texture.m_format;

        _texture.bind();
        GLint width = 0;
        GLint height = 0;
        GLint depth = 0;
        GLint destFormat = 0;
        switch(m_type)
        {
        case TT_1D :
            glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
            glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_HEIGHT, &height);
            glGetTexLevelParameteriv(GL_TEXTURE_1D, 0, GL_TEXTURE_DEPTH, &depth);
            break;
        case TT_2D :
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &destFormat);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
            glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_DEPTH, &depth);
            break;
        case TT_2DMULTISAMPLE :
            GLNGINE_EXCEPTION("TODO");
        default:
            GLNGINE_EXCEPTION("Unhandle texture type");
        }

        size_t numBytes = size_t(width * height * depth) * 4;
        std::vector< unsigned char > data(numBytes);
        if(numBytes > 0)
        {
            switch(m_type)
            {
            case TT_1D :
            {
                glGetTexImage(GL_TEXTURE_1D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                bind();
                glTexImage1D(GL_TEXTURE_1D, 0, destFormat, width, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
            }
                break;
            case TT_2D :
            {
                glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
                bind();
                glTexImage2D(GL_TEXTURE_2D, 0, destFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, &data[0]);
            }
                break;
            case TT_2DMULTISAMPLE :
                GLNGINE_EXCEPTION("TODO");
            default:
                GLNGINE_EXCEPTION("Unhandle texture type");
            }
            unbind();
        }
        GLNGINE_CHECK_GL;
    }
    return *this;
}

void Texture::setActiveTexture(int _location)
{
    if(_location > s_MAX_LOCATION)
    {
        GLNGINE_EXCEPTION("Active location overflow");
    }
    glActiveTexture(GLenum(GL_TEXTURE0 + _location));

}

void Texture::load(const std::filesystem::path& _path, TEXTURE_TYPE _type, TEXTURE_INTERNAL_FORMAT _internalFormat)
{
    GLNGINE_ASSERT_IF(!std::filesystem::exists(_path), std::filesystem::is_regular_file(_path));

    m_type = _type;

    bool hasAlpha;
    const std::string fileFormat = _path.extension().string();
    if(fileFormat == ".bmp" || fileFormat == ".jpg" || fileFormat == ".jpeg")
    {
        hasAlpha = false;
    }
    else if(fileFormat == ".png" || fileFormat == ".tga" || fileFormat == ".psd" || fileFormat == ".DDS")
    {
        hasAlpha = true;
    }
    else
    {
        GLNGINE_EXCEPTION("Can't open '" + fileFormat + "' file");
    }

    int width, height, chanel;
    unsigned char* data;
    int soilFormat = SOIL_LOAD_RGB;
    m_format = TF_RGB;
    if(hasAlpha)
    {
        soilFormat = SOIL_LOAD_RGBA;
        m_format = TF_RGBA;
    }
    data = SOIL_load_image(_path.string().c_str(), &width, &height, &chanel, soilFormat);
    if(width < 0 || width > s_MAX_SIZE || height < 0 || height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Texture size too large");
    }
    switch(_type)
    {
    case TT_1D :
        if(height != 1)
        {
            GLNGINE_EXCEPTION("Not a 1D texture");
        }
        glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, width, 0, m_format, GL_UNSIGNED_BYTE, data);
        break;
    case TT_2D :
        glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);
        break;
    case TT_2DMULTISAMPLE :
        GLNGINE_EXCEPTION("Can't load image to multisampled textures");
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
    SOIL_free_image_data(data);
}

void Texture::allocate(TEXTURE_TYPE _type, int _width, int _height, TEXTURE_INTERNAL_FORMAT _internalFormat, TEXTURE_FORMAT _format, TEXTURE_DATA _data)
{
    if(_width > s_MAX_SIZE || _height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Texture size too large");
    }

    m_format = _format;
    m_type = _type;

    switch (m_type)
    {
    case TT_1D :
        if(_height != 1)
        {
            GLNGINE_EXCEPTION("Not a 1D texture");
        }
        glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, _width, 0, _format, _data, nullptr);
        break;
    case TT_2D :
        glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, _data, nullptr);
        break;
    case TT_2DMULTISAMPLE :
        GLNGINE_EXCEPTION("Can't allocate multisampled textures without sample");
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
        break;
    }
    GLNGINE_CHECK_GL;
}

void Texture::allocateMultisample(TEXTURE_TYPE _type, int _width, int _height, TEXTURE_INTERNAL_FORMAT _internalFormat, int _sample)
{
    if(_width > s_MAX_SIZE || _height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Size too big");
    }
    if(_sample > s_MAX_SAMPLE)
    {
        GLNGINE_EXCEPTION("Sample too hight");
    }

    m_type = _type;

    switch (m_type)
    {
    case TT_1D :
    case TT_2D :
        GLNGINE_EXCEPTION("Can't allocate multisample to no multisampled textures");
        break;
    case TT_2DMULTISAMPLE :
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _sample, GLenum(_internalFormat), _width, _height, GL_TRUE);
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
}

void Texture::generateMipmap() const
{
    switch(m_type)
    {
    case TT_1D :
        glGenerateMipmap(GL_TEXTURE_1D);
        break;
    case TT_2D :
        glGenerateMipmap(GL_TEXTURE_2D);
        break;
    case TT_2DMULTISAMPLE :
        GLNGINE_EXCEPTION("Can't generate mipmap to multisampled textures");
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
}

void Texture::bind() const
{
    switch(m_type)
    {
    case TT_1D :
        glBindTexture(GL_TEXTURE_1D, m_id);
        break;
    case TT_2D :
        glBindTexture(GL_TEXTURE_2D, m_id);
        break;
    case TT_2DMULTISAMPLE :
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_id);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
}

void Texture::unbind() const
{
    switch(m_type)
    {
    case TT_1D :
        glBindTexture(GL_TEXTURE_1D, 0);
        break;
    case TT_2D :
        glBindTexture(GL_TEXTURE_2D, 0);
        break;
    case TT_2DMULTISAMPLE :
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
}

void Texture::setMinFilter(TEXTURE_FILTER _filter) const
{
#ifdef GLNGINE_USE_STATE_CACHE

    if(m_minFilter != _filter)
    {
        m_minFilter = _filter;
#endif
        switch(m_type)
        {
        case TT_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, _filter);
            break;
        case TT_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filter);
            break;
        case TT_2DMULTISAMPLE :
            GLNGINE_EXCEPTION("Can't set filter to multisampled textures");
        default:
            GLNGINE_EXCEPTION("Unhandle texture type");
        }
        GLNGINE_CHECK_GL;
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

void Texture::setMagFilter(TEXTURE_FILTER _filter) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    GLNGINE_ASSERT_IF(!(_filter == TF_LINEAR || _filter == TF_NEAREST), "Unhandle filter type");
    if(m_magFilter != _filter)
    {
        m_magFilter = _filter;
#endif
        switch(m_type)
        {
        case TT_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, _filter);
            break;
        case TT_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filter);
            break;
        case TT_2DMULTISAMPLE :
            GLNGINE_EXCEPTION("Can't set filter to multisampled textures");
        default:
            GLNGINE_EXCEPTION("Unhandle texture type");
        }
        GLNGINE_CHECK_GL;
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

void Texture::setUWrap(WRAP_MODE _mode) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(m_uWrap != _mode)
    {
        m_uWrap = _mode;
#endif
        switch(m_type)
        {
        case TT_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, _mode);
            break;
        case TT_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _mode);
            break;
        case TT_2DMULTISAMPLE :
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, _mode);
        default:
            GLNGINE_EXCEPTION("Unhandle wrap mode");
        }
        GLNGINE_CHECK_GL;
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

void Texture::setVWrap(WRAP_MODE _mode) const
{
#ifdef GLNGINE_USE_STATE_CACHE
    if(m_vWrap != _mode)
    {
        m_vWrap = _mode;
#endif
        switch(m_type)
        {
        case TT_1D :
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, _mode);
            break;
        case TT_2D :
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _mode);
            break;
        case TT_2DMULTISAMPLE :
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, _mode);
        default:
            GLNGINE_EXCEPTION("Unhandle wrap mode");
        }
        GLNGINE_CHECK_GL;
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

Texture::Initializer::Initializer()
{
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_MAX_LOCATION);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &s_MAX_SIZE);
    glGetIntegerv(GL_MAX_SAMPLES, &s_MAX_SAMPLE);
}

}

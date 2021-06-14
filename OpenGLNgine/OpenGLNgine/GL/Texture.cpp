#include "OpenGLNgine/GL/Texture.hpp"

#include "OpenGLNgine/Core/Exception.hpp"

#include <SOIL2/SOIL2.h>
#include <iostream>
namespace GL
{


#ifdef GLNGINE_USE_STATE_CACHE
ptrdiff_t Texture::s_cache = reinterpret_cast< ptrdiff_t >(nullptr);

int Texture::s_activeTextUnit = 0;
#endif

GLint Texture::s_MAX_SIZE = 0;

GLint Texture::s_MAX_SAMPLE = 0;

GLint Texture::s_MAX_LOCATION = 0;

GLenum Texture::getBaseFormat(TEXTURE_INTERNAL_FORMAT _format)
{
    switch(_format)
    {
    case TIF_DEPTH:
    case TIF_DEPTH16:
    case TIF_DEPTH24:
    case TIF_DEPTH32:
        return GL_DEPTH_COMPONENT;
    case TIF_DEPTH_STENCIL:
    case TIF_DEPTH24_STENCIL8:
    case TIF_DEPTH32F_STENCIL8:
        return GL_DEPTH_STENCIL;
    case TIF_STENCIL_INDEX8:
        return GL_STENCIL_INDEX;
    case TIF_RED:
    case TIF_R8:
    case TIF_R8_SNORM:
    case TIF_R16:
    case TIF_R16_SNORM:
    case TIF_R3_G3_B2:
    case TIF_R16F:
    case TIF_R32F:
    case TIF_R11F_G11F_B10F:
        return GL_RED;
    case TIF_R8I:
    case TIF_R8UI:
    case TIF_R16I:
    case TIF_R16UI:
    case TIF_R32I:
    case TIF_R32UI:
        return GL_RED_INTEGER;
    case TIF_RG:
    case TIF_RG8:
    case TIF_RG8_SNORM:
    case TIF_RG16:
    case TIF_RG16_SNORM:
    case TIF_RG16F:
    case TIF_RG32F:
        return GL_RG;
    case TIF_RG8I:
    case TIF_RG8UI:
    case TIF_RG16I:
    case TIF_RG16UI:
    case TIF_RG32I:
    case TIF_RG32UI:
        return GL_RG_INTEGER;
    case TIF_RGB:
    case TIF_RGB4:
    case TIF_RGB5:
    case TIF_RGB8:
    case TIF_RGB8_SNORM:
    case TIF_RGB10:
    case TIF_RGB12:
    case TIF_RGB16_SNORM:
    case TIF_RGB5_A1:
    case TIF_RGB10_A2:
    case TIF_RGB10_A2UI:
    case TIF_SRGB8:
    case TIF_RGB16F:
    case TIF_RGB32F:
    case TIF_RGB9_E5:
        return GL_RGB;
    case TIF_RGB8I:
    case TIF_RGB8UI:
    case TIF_RGB16I:
    case TIF_RGB16UI:
    case TIF_RGB32I:
    case TIF_RGB32UI:
        return GL_RGB_INTEGER;
    case TIF_RGBA:
    case TIF_RGBA2:
    case TIF_RGBA4:
    case TIF_RGBA8:
    case TIF_RGBA8_SNORM:
    case TIF_RGBA12:
    case TIF_RGBA16:
    case TIF_RGBA16F:
    case TIF_RGBA32F:
    case TIF_SRGB8_ALPHA8:
        return GL_RGBA;
    case TIF_RGBA8I:
    case TIF_RGBA8UI:
    case TIF_RGBA16I:
    case TIF_RGBA16UI:
    case TIF_RGBA32I:
    case TIF_RGBA32UI:
        return GL_RGBA_INTEGER;
    default:
        GLNGINE_EXCEPTION("Unhandle texture format");
    }
}

GLenum Texture::getBaseType(TEXTURE_INTERNAL_FORMAT _format)
{
    switch(_format)
    {
    case TIF_DEPTH24_STENCIL8:
        return GL_UNSIGNED_INT_24_8;
    case TIF_R8:
    case TIF_RG8:
    case TIF_RGB8:
    case TIF_RGBA8:
    case TIF_STENCIL_INDEX8:
        return GL_UNSIGNED_BYTE;
    case TIF_R3_G3_B2:
        return GL_UNSIGNED_BYTE_3_3_2;
    case TIF_R8_SNORM:
    case TIF_RG8_SNORM:
    case TIF_RGB8_SNORM:
    case TIF_RGBA8_SNORM:
        return GL_BYTE;
    case TIF_DEPTH16:
    case TIF_R16:
    case TIF_RG16:
    case TIF_RGBA16:
        return GL_UNSIGNED_SHORT;
    case TIF_RGB4:
    case TIF_RGBA4:
        return GL_UNSIGNED_SHORT_4_4_4_4;
    case TIF_RGB5:
    case TIF_RGB5_A1:
        return GL_UNSIGNED_SHORT_5_5_5_1;
    case TIF_R16_SNORM:
    case TIF_RG16_SNORM:
    case TIF_RGB16_SNORM:
        return GL_SHORT;
    case TIF_R8UI:
    case TIF_R16UI:
    case TIF_R32UI:
    case TIF_RG8UI:
    case TIF_RG16UI:
    case TIF_RG32UI:
    case TIF_RGB8UI:
    case TIF_RGB16UI:
    case TIF_RGB32UI:
    case TIF_RGBA16UI:
    case TIF_RGBA32UI:
        return GL_UNSIGNED_INT;
    case TIF_RGBA8UI:
    case TIF_SRGB8_ALPHA8:
    case TIF_SRGB8:
        return GL_UNSIGNED_INT_8_8_8_8;
    case TIF_RGB10:
    case TIF_RGB10_A2UI:
    case TIF_RGB10_A2:
        return GL_UNSIGNED_INT_10_10_10_2;
    case TIF_R8I:
    case TIF_R16I:
    case TIF_R32I:
    case TIF_RG8I:
    case TIF_RG16I:
    case TIF_RG32I:
    case TIF_RGB8I:
    case TIF_RGB16I:
    case TIF_RGB32I:
    case TIF_RGBA8I:
    case TIF_RGBA16I:
    case TIF_RGBA32I:
        return GL_INT;
    case TIF_DEPTH:
    case TIF_DEPTH24:
    case TIF_DEPTH32:
    case TIF_RED:
    case TIF_RG:
    case TIF_RGB:
    case TIF_RGBA:
    case TIF_R16F:
    case TIF_R32F:
    case TIF_R11F_G11F_B10F:
    case TIF_RG16F:
    case TIF_RG32F:
    case TIF_RGB16F:
    case TIF_RGB32F:
    case TIF_RGBA16F:
    case TIF_RGBA32F:
        return GL_FLOAT;
    case TIF_DEPTH_STENCIL:
    case TIF_DEPTH32F_STENCIL8:
    case TIF_RGB12:
    case TIF_RGB9_E5:
    case TIF_RGBA2:
    case TIF_RGBA12:
    default:
        GLNGINE_EXCEPTION("Unhandle texture format");
    }
}

Texture::Texture(TEXTURE_TYPE _type) :
    IBindable(),
    m_type(_type)
{
    [[maybe_unused]] static const void* initializer = []()
    {
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &s_MAX_LOCATION);
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &s_MAX_SIZE);
        glGetIntegerv(GL_MAX_SAMPLES, &s_MAX_SAMPLE);
        GLNGINE_CHECK_GL;
        return nullptr;
    } ();

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
    GLNGINE_ASSERT_IF(m_type != _texture.m_type, "Texture source and destination must be the same");
    if(this != &_texture)
    {
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
#ifdef GLNGINE_USE_STATE_CACHE
    if(s_activeTextUnit != _location)
    {
        s_activeTextUnit = _location;
#endif
        glActiveTexture(GLenum(GL_TEXTURE0 + _location));
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

void Texture::load(const std::filesystem::path& _path, TEXTURE_INTERNAL_FORMAT _internalFormat)
{
    GLNGINE_ASSERT_IF(!std::filesystem::exists(_path) || !std::filesystem::is_regular_file(_path), ("The file '" + _path.string() + "' does not exist").c_str());

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
    switch(m_type)
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

void Texture::allocate(int _width, int _height, TEXTURE_INTERNAL_FORMAT _internalFormat, int _sample)
{
    GLNGINE_ASSERT_IF(_width<0 || _height<0, "The texture size musn't be negativ");
    if(_width > s_MAX_SIZE || _height > s_MAX_SIZE)
    {
        GLNGINE_EXCEPTION("Texture size too large");
    }
    if(_sample > s_MAX_SAMPLE)
    {
        GLNGINE_EXCEPTION("Sample too hight");
    }

    switch(m_type)
    {
    case TT_1D :
        if(_height != 1)
        {
            GLNGINE_EXCEPTION("Not a 1D texture");
        }
        glTexImage1D(GL_TEXTURE_1D, 0, _internalFormat, _width, 0, getBaseFormat(_internalFormat), getBaseType(_internalFormat), nullptr);
        break;
    case TT_2D :
        glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, getBaseFormat(_internalFormat), getBaseType(_internalFormat), nullptr);
        break;
    case TT_2DMULTISAMPLE :
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, _sample, _internalFormat, _width, _height, GL_TRUE);
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
        break;
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
        break;
    default:
        GLNGINE_EXCEPTION("Unhandle texture type");
    }
    GLNGINE_CHECK_GL;
}

void Texture::bind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(this);
    if(s_cache != add || m_textUnit != s_activeTextUnit)
    {
        s_cache = add;
        m_textUnit = s_activeTextUnit;
#endif
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
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
}

void Texture::unbind() const
{
#ifdef GLNGINE_USE_STATE_CACHE
    ptrdiff_t add = reinterpret_cast< ptrdiff_t >(nullptr);
    if(s_cache != add || m_textUnit != s_activeTextUnit)
    {
        s_cache = add;
        m_textUnit = s_activeTextUnit;
#endif
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
#ifdef GLNGINE_USE_STATE_CACHE
    }
#endif
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

void Texture::setUWrap(TEXTURE_WRAP _mode) const
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

void Texture::setVWrap(TEXTURE_WRAP _mode) const
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

}

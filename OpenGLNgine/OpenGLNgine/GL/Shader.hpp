#pragma once

#include <GL/glew.h>

#include <filesystem>
#include <string>

namespace GL
{

/// Manages all shader types.
enum SHADER_TYPE : GLenum
{
    ST_VERTEX = GL_VERTEX_SHADER, ///< Vertex shader.
    ST_GEOMETRY = GL_GEOMETRY_SHADER, ///< Geometry shader.
    ST_FRAGMENT = GL_FRAGMENT_SHADER ///< Fragment shader.
};

/**
 * @brief Manages a shader object
 */
class Shader final
{

public:

    /**
     * @brief Creates a shader object.
     * @param _type Specifies the type of shader to be created.
     */
    Shader(SHADER_TYPE _type);

    /// Deletes the shader object.
    ~Shader();

    /**
     * @brief Creates a shader copied from the parameter, without compiling it.
     * @param _shader The shader to copy.
     */
    Shader(const Shader& _shader);

    /**
     * @brief Destroys and creates a shader copied from the parameter, without compiling it.
     * @param _shader The shader to copy.
     * @return The current shader.
     */
    Shader& operator=(const Shader& _shader);

    /// Deleted move constructor.
    Shader(Shader&&) = delete;

    /// Deleted move operator.
    Shader& operator=(Shader&&) = delete;

    /**
     * @brief Gets the type of the shader.
     * @return The type of the shader.
     */
    inline SHADER_TYPE getType() const;

    /**
     * @brief Gets the GL data ID.
     * @return The GL data ID.
     */
    inline GLuint getId() const;

    /**
     * @brief Sets the source code.
     * @param _src The source code.
     */
    inline void setSource(const std::string& _src);

    /**
     * @brief Sets the source code from a file.
     * @param _path The path of the source code file.
     */
    void setSourceFromFile(const std::filesystem::path& _path);

    /// Compile the shader.
    void compile() const;

private:

    /// Defines the ID of the GL data.
    GLuint m_id {0};

    /// Defines the type of the shader.
    SHADER_TYPE m_type {ST_VERTEX};

    /// Stores the source code of the shader.
    std::string m_sources {};

};

inline SHADER_TYPE Shader::getType() const
{
    return m_type;
}

inline GLuint Shader::getId() const
{
    return m_id;
}

inline void Shader::setSource(const std::string& _src)
{
    m_sources = _src;
}

}

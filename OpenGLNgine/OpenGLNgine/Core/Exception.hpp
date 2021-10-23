#pragma once

#include <cassert>
#include <stdexcept>
#include <string>

#define GLNGINE_ASSERT_IF(_cond, _message) assert(!(_cond) && (_message))

#define GLNGINE_ASSERT(_message) GLNGINE_ASSERT_IF(false, _message)

#define GLNGINE_EXCEPTION(_message) throw std::runtime_error ((std::string("[") + __FUNCTION__ + "] " + _message + ".").c_str())

#ifdef NDEBUG
#define GLNGINE_CHECK_GL
#else
#define GLNGINE_CHECK_GL { \
        GLenum code = glGetError(); \
        if(code != GL_NO_ERROR) \
        { \
            std::string message = std::string((char*)gluErrorString(code)); \
            while((code = glGetError()) != GL_NO_ERROR) \
                message += " " + std::string((char*)gluErrorString(code)); \
            throw std::runtime_error((std::string("[") + __FUNCTION__ + "] OpenGL error: " + message + ".").c_str()); \
        } \
    }
#endif

#include "GL/Buffer.hpp"

using namespace std;

namespace GL
{
    Buffer::Buffer(BUFFER_TYPE type)
        : m_type(type)
	{
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(bufferType type)]..." << endl;
#endif
		switch (type)
		{
        case BUFFER_TYPE::VAO:
            glGenVertexArrays(1, &m_id);
			break;
        case BUFFER_TYPE::VBO:
            glGenBuffers(1, &m_id);
			break;
        case BUFFER_TYPE::EBO:
            glGenBuffers(1, &m_id);
			break;
		default:
            glGenBuffers(1, &m_id);
			break;
		}
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(bufferType type)]...\tsuccess" << endl;
#endif
	}

	Buffer::~Buffer()
	{
#ifdef _DEBUG
		cout << "[Buffer] [~Buffer()]..." << endl;
#endif
        glDeleteBuffers(1, &m_id);
#ifdef _DEBUG
		cout << "[Buffer] [~Buffer()]...\tsuccess" << endl;
#endif
	}

	Buffer::Buffer(const Buffer& buffer) throw()
        : m_type(buffer.getType())
	{
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(const Buffer& buffer) throw()]..." << endl;
#endif
        switch (m_type)
		{
        case BUFFER_TYPE::VAO:
			throw invalid_argument("[Buffer] [Buffer(const Buffer& buffer)] can't copying VAO");
			break;
        case BUFFER_TYPE::VBO:
            glGenBuffers(1, &m_id);
			break;
        case BUFFER_TYPE::EBO:
            glGenBuffers(1, &m_id);
			break;
		default:
            glGenBuffers(1, &m_id);
			break;
		}

		glBindBuffer(GL_COPY_READ_BUFFER,buffer.getId());
		glBindBuffer(GL_COPY_WRITE_BUFFER, getId());

		GLint size = 0;
		glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
		if (size != 0) 
		{
			glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
		}

		glBindBuffer(GL_COPY_READ_BUFFER, 0);
		glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(const Buffer& buffer) throw()]...\tsuccess" << endl;
#endif
	}

	Buffer& Buffer::operator=(const Buffer& buffer) throw()
	{
#ifdef _DEBUG
		cout << "[Buffer] [operator=(const Buffer& buffer) throw()]..." << endl;
#endif
		if (this != &buffer)
		{
            glDeleteBuffers(1, &m_id);
            m_type = buffer.getType();
            switch (m_type)
			{
            case BUFFER_TYPE::VAO:
				throw invalid_argument("[Buffer] [operator=(const Buffer& buffer) throw()] can't copying VAO");
				break;
            case BUFFER_TYPE::VBO:
                glGenBuffers(1, &m_id);
				break;
            case BUFFER_TYPE::EBO:
                glGenBuffers(1, &m_id);
				break;
			default:
                glGenBuffers(1, &m_id);
				break;
			}

			glBindBuffer(GL_COPY_READ_BUFFER, buffer.getId());
			glBindBuffer(GL_COPY_WRITE_BUFFER, getId());

			GLint size = 0;
			glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &size);
			if (size != 0)
			{
				glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, GL_STATIC_DRAW);
				glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
			}

			glBindBuffer(GL_COPY_READ_BUFFER, 0);
			glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
		}
		return *this;
#ifdef _DEBUG
		cout << "[Buffer] [operator=(const Buffer& buffer) throw()]...\tsuccess" << endl;
#endif
	}

    BUFFER_TYPE Buffer::getType() const
	{
        return m_type;
	}

	GLuint Buffer::getId() const
	{
        return m_id;
	}

	void Buffer::bind() const
	{
        switch (m_type)
		{
		case VAO:
            glBindVertexArray(m_id);
			break;
		case VBO:
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
			break;
		case EBO:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			break;
		default:
            glBindBuffer(GL_ARRAY_BUFFER, m_id);
			break;
		}
	}

	void Buffer::unbind() const
	{
        switch (m_type)
		{
		case VAO:
			glBindVertexArray(0);
			break;
		case VBO:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		case EBO:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			break;
		default:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;
		}
	}
}

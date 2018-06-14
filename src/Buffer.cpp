#include "Buffer.h"

using namespace std;

namespace GL
{
	Buffer::Buffer(bufferType type)
		: _type(type)
	{
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(bufferType type)]..." << endl;
#endif
		switch (type)
		{
		case bufferType::VAO:
			glGenVertexArrays(1, &_id);
			break;
		case bufferType::VBO:
			glGenBuffers(1, &_id);
			break;
		case bufferType::EBO:
			glGenBuffers(1, &_id);
			break;
		default:
			glGenBuffers(1, &_id);
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
		glDeleteBuffers(1, &_id);
#ifdef _DEBUG
		cout << "[Buffer] [~Buffer()]...\tsuccess" << endl;
#endif
	}

	Buffer::Buffer(const Buffer& buffer) throw(...)
		: _type(buffer.type())
	{
#ifdef _DEBUG
		cout << "[Buffer] [Buffer(const Buffer& buffer) throw(...)]..." << endl;
#endif
		switch (_type)
		{
		case bufferType::VAO:
			throw invalid_argument("[Buffer] [Buffer(const Buffer& buffer)] can't copying VAO");
			break;
		case bufferType::VBO:
			glGenBuffers(1, &_id);
			break;
		case bufferType::EBO:
			glGenBuffers(1, &_id);
			break;
		default:
			glGenBuffers(1, &_id);
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
		cout << "[Buffer] [Buffer(const Buffer& buffer) throw(...)]...\tsuccess" << endl;
#endif
	}

	Buffer& Buffer::operator=(const Buffer& buffer) throw(...)
	{
#ifdef _DEBUG
		cout << "[Buffer] [operator=(const Buffer& buffer) throw(...)]..." << endl;
#endif
		if (this != &buffer)
		{
			glDeleteBuffers(1, &_id);
			_type = buffer.type();
			switch (_type)
			{
			case bufferType::VAO:
				throw invalid_argument("[Buffer] [operator=(const Buffer& buffer) throw(...)] can't copying VAO");
				break;
			case bufferType::VBO:
				glGenBuffers(1, &_id);
				break;
			case bufferType::EBO:
				glGenBuffers(1, &_id);
				break;
			default:
				glGenBuffers(1, &_id);
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
		cout << "[Buffer] [operator=(const Buffer& buffer) throw(...)]...\tsuccess" << endl;
#endif
	}

	bufferType Buffer::type() const
	{
		return _type;
	}

	GLuint Buffer::getId() const
	{
		return _id;
	}

	void Buffer::bind() const
	{
		switch (_type)
		{
		case VAO:
			glBindVertexArray(_id);
			break;
		case VBO:
			glBindBuffer(GL_ARRAY_BUFFER, _id);
			break;
		case EBO:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
			break;
		default:
			glBindBuffer(GL_ARRAY_BUFFER, _id);
			break;
		}
	}

	void Buffer::unbind() const
	{
		switch (_type)
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

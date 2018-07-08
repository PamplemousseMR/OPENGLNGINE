#include "GL/Texture.h"

using namespace std;

namespace GL
{
	vector<bool> Texture::s_location;
	bool Texture::s_first = false;

	Texture::Texture(textureType type)
		: _type(type), _location(-1), _hasAlpha(false)
	{
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [Texture(textureType type)]..." << endl;
#endif
		if (!s_first)
		{
			GLint size;
			glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);
			for (int i(0); i < size; i++)
				s_location.push_back(false);
			s_first = true;
		}
		glGenTextures(1, &_id);
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [Texture(textureType type)]...\tsuccess" << endl;
#endif
	}


	Texture::~Texture()
	{
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [~Texture()]..." << endl;
#endif
		glDeleteTextures(1, &_id);
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [~Texture()]...\tsuccess" << endl;
#endif
	}

	GLuint Texture::getId() const
	{
		return _id;
	}

	int Texture::getLocation() const
	{
		return _location;
	}

	textureType Texture::getType() const
	{
		return _type;
	}

	const string& Texture::getName() const
	{
		return _name;
	}

	int Texture::load(const char* imagepath) throw(...)
	{
		_name = imagepath;
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [load(const char* imagepath) throw(...)]..." << endl;
#endif
		FILE * file;
		fopen_s(&file,imagepath, "rb");
		string name = imagepath;
		if (!file)
			throw invalid_argument("[Texture " + _name + "] [load(const char* imagepath) throw(...)] can't open file : " + name);

		string path = imagepath;
		string fileFormat = "";
		for (int i((int)path.length() - 1); i > 0; i--)
		{
			if (path[i] == '.')
				break;
			else
				fileFormat.push_back(path[i]);
		}
		reverse(fileFormat.begin(), fileFormat.end());
		if (fileFormat == "bmp" || fileFormat == "jpg" || fileFormat == "jpeg")
			_hasAlpha = false;
		else if (fileFormat == "png" || fileFormat == "tga" || fileFormat == "psd" || fileFormat == "DDS")
			_hasAlpha = true;
		else if (fileFormat == "hdr")
			throw invalid_argument("[Texture " + _name + "] [load(const char* imagepath) throw(...)] TODO HDR");
		else
			throw invalid_argument("[Texture " + _name + "] [load(const char* imagepath) throw(...)] can't load : " + fileFormat + " file");
		int width, height, chanel;
		unsigned char* data;
		int soilFormat = SOIL_LOAD_RGB;
		GLuint internalFormat = GL_RGB;
		GLenum format = GL_RGB;
		if (_hasAlpha)
		{
			soilFormat = SOIL_LOAD_RGBA;
			internalFormat = GL_RGBA;
			format = GL_RGBA;
		}
		data = SOIL_load_image(imagepath, &width, &height, &chanel, soilFormat);
		switch (_type)
		{
			case TEXTURE_1D :
				if (height != 0)
					throw invalid_argument("[Texture " + _name + "] [load(const char* imagepath) throw(...)] not a 1D texture");
				glTexImage1D(_type, 0, internalFormat, width, 0, format, GL_UNSIGNED_BYTE, data);
			break;
			case TEXTURE_2D :
				glTexImage2D(_type, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			break;
		}
		SOIL_free_image_data(data);
#ifdef _DEBUG
		cout << "[Texture " << _name << "] [load(const char* imagepath) throw(...)]...\tsuccess" << endl;
#endif
		return width;
	}


	void Texture::setParameter(GLenum pname, GLint param) const
	{
		glTexParameteri(_type, pname, param);
	}

	void Texture::generateMipmap() const
	{
		glGenerateMipmap(_type);
	}

	void Texture::bind() throw(...)
	{
		for (int i(0); i < s_location.size(); i++)
			if (s_location[i] == false)
			{
				_location = i;
				s_location[i] = true;
				break;
			}
		if (_location == -1)
			throw invalid_argument("[Texture " + _name + "] [bind() throw(...)] too much bind texture");
		glActiveTexture(GL_TEXTURE0 + _location);
		glBindTexture(_type, _id);
	}

	void Texture::unbind()
	{
		s_location[_location] = false;
		_location = -1;
		glBindTexture(_type, 0);
	}

}

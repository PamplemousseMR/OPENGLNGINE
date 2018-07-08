#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <string>
#include <iostream>
#include <map>

namespace GL
{
	class Buffer;
}

namespace Component
{
	class Mesh
	{

	private:

		int _dataSize;
		GL::Buffer* _vboVertex;
		GL::Buffer* _vboNormal;
		GL::Buffer* _vboTextCoord;
		GL::Buffer* _vboTangent;
		GL::Buffer* _vboBitangent;
		GL::Buffer* _ebo;
		GL::Buffer* _vao;
		std::string _name;
		bool _normal;
		bool _textCoord;

		struct PackedVertex 
		{
			glm::vec3 position;
			glm::vec2 uv;
			glm::vec3 normal;
			bool operator<(const PackedVertex that) const 
			{
				return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
			};
		};

		bool getSimilarVertexIndex(const PackedVertex&, const std::map<PackedVertex, unsigned int>&, unsigned int&);
		void Mesh::indexVBO(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&, std::vector<unsigned int>&, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);
	
	public:

		static const int S_VERTEXLOCATION;
		static const int S_TEXTCOORDLOCATION;
		static const int S_NORMALLOCATION;

		Mesh(const std::string&);
		~Mesh();

		void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&) throw(...);
		void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&) throw(...);
		void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec2>&, const std::vector<glm::vec3>&) throw(...);
		void loadMesh(const std::vector<glm::vec3>&, const std::vector<glm::vec3>&, const std::vector<glm::vec3>&) throw(...);
		void bind() const;
		void unbind() const;
		void draw() const;

		GL::Buffer* getArrayBuffer() const;
		const std::string& getName() const;
		int getVertexLocation() const;
		int getTextureCoordLocation() const;
		int getNormalLocation() const;
		bool hasTextureCoord() const;
		bool hasNormal() const;

		std::ostream& print(std::ostream&) const;

	};

	std::ostream& operator<<(std::ostream&, const Mesh&);
}

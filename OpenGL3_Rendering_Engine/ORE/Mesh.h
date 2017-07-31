#pragma once
#include "BaseMesh.h"
#include "Engine.h"

using std::vector;

namespace ORE {
	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	class Mesh :
		public BaseMesh {
	public:
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<GLuint> textures);
		virtual ~Mesh();
		void draw(World* world) override;
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		GLuint program;

		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<GLuint> textures;
		float shininess;
		void setupMesh();
	};
}

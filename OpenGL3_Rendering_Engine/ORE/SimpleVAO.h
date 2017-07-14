#pragma once
#include "Engine.h"
#include "Mesh.h"
#include <vector>

namespace ORE {
	class SimpleVAO :
		public Mesh {
	public:
		SimpleVAO(GLuint texture = NULL, GLuint specular = NULL, float shininess = 0);
		~SimpleVAO();
		// Draws the vertex array object
		void draw(World* world) override;
		// Sets the arrays for the mesh
		void setMesh(std::vector<GLfloat> vert, std::vector<GLfloat> uv, std::vector<GLfloat> norm);
	private:
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvs;
		std::vector<GLfloat> normals;
		GLuint vertexArray;
		GLuint vertexBuffer;
		GLuint uvBuffer;
		GLuint normalBuffer;
		GLuint program;
		GLuint texture;
		GLuint specular;
		float shininess;
	};
}

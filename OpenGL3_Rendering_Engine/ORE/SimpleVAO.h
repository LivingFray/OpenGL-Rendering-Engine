#pragma once
#include "Engine.h"
#include "BaseMesh.h"
#include <vector>

namespace ORE {
	class SimpleVAO :
		public BaseMesh {
	public:
		SimpleVAO();
		~SimpleVAO();
		// Draws the vertex array object
		void draw(World* world) override;
		// Sets the arrays for the mesh
		void setMesh(std::vector<GLfloat> vert, std::vector<GLfloat> uv, std::vector<GLfloat> norm);
		// Sets the shininess of the mesh
		void setShininess(float shininess);
		// Sets the texture of the mesh
		void setTexture(GLuint texture);
		// Sets the specular map of the mesh
		void setSpecular(GLuint specular);
		// Sets the emission map of the mesh
		void setEmission(GLuint emission);
		// Sets the normal map of the mesh
		void setNormal(GLuint normal);
	private:
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvs;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> tangents;
		std::vector<GLfloat> bitangents;
		GLuint vertexArray;
		GLuint vertexBuffer;
		GLuint uvBuffer;
		GLuint normalBuffer;
		GLuint tangentBuffer;
		GLuint bitangentBuffer;
		GLuint program;
		GLuint texture;
		GLuint specular;
		float shininess;
		GLuint emission;
		GLuint normal;
	};
}

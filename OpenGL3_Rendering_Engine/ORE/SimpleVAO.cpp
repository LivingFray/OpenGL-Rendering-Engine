#include "SimpleVAO.h"

namespace ORE {
	SimpleVAO::SimpleVAO(){
		//program = getProgram("simpleMesh");
		program = getProgram("singleLight");
		glGenVertexArrays(1, &vertexArray);
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &uvBuffer);
		glGenBuffers(1, &normalBuffer);
		glGenBuffers(1, &tangentBuffer);
		glGenBuffers(1, &bitangentBuffer);
		glUseProgram(program);
		glUniform1i(glGetUniformLocation(program, "texture"), 0);
		glUniform1i(glGetUniformLocation(program, "specular"), 1);
		glUniform1i(glGetUniformLocation(program, "normalMap"), 2);
		glUniform1i(glGetUniformLocation(program, "emissionMap"), 3);
		glUseProgram(0);
	}


	SimpleVAO::~SimpleVAO() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteBuffers(1, &normalBuffer);
		glDeleteBuffers(1, &tangentBuffer);
		glDeleteBuffers(1, &bitangentBuffer);
		glDeleteVertexArrays(1, &vertexArray);
	}


	// Draws the vertex array object
	void SimpleVAO::draw(World* world) {
		Camera cam = *(world->getCamera());
		//Use correct shaders
		glUseProgram(program);
		//Enable the VAO
		glBindVertexArray(vertexArray);
		//Pass texture to shaders
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, normal);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emission);
		//Shininess
		glUniform1f(glGetUniformLocation(program, "shininess"), shininess);
		//Update lighting AGAIN TEMP
		world->getLight()->updateShader(program);
		//Pass matrices to shader
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, &(this->getGlobalMatrix())[0][0]);
		glm::mat3 inv = glm::mat3(glm::transpose(glm::inverse(this->getGlobalMatrix())));
		glUniformMatrix3fv(glGetUniformLocation(program, "transInvModel"), 1, false, &inv[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, false, &(cam.getView())[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, &(cam.getProjection())[0][0]);
		//Pass the camera position
		glUniform3fv(glGetUniformLocation(program, "viewPos"), 1, &(cam.getPosition())[0]);
		//Pass the MVP matrix to the shaders
		//glUniformMatrix4fv(mvpUniform, 1, false, &mvp[0][0]);
		//Draw the VAO
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	}


	// Sets the arrays for the mesh
	void SimpleVAO::setMesh(std::vector<GLfloat> vert, std::vector<GLfloat> uv, std::vector<GLfloat> norm) {
		vertices = vert;
		uvs = uv;
		normals = norm;
		glBindVertexArray(vertexArray);
		//Pass vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Pass UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), &uvs[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Pass normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Calculate tangents + bitangents (Doesn't average)
		for (unsigned int i = 0; i < vertices.size()/9; i++) {
			//Positions
			glm::vec3 pos1 = glm::vec3(vertices[9 * i + 0], vertices[9 * i + 1], vertices[9 * i + 2]);
			glm::vec3 pos2 = glm::vec3(vertices[9 * i + 3], vertices[9 * i + 4], vertices[9 * i + 5]);
			glm::vec3 pos3 = glm::vec3(vertices[9 * i + 6], vertices[9 * i + 7], vertices[9 * i + 8]);
			//Texture coords
			glm::vec2 uv1 = glm::vec2(uvs[6 * i + 0], uvs[6 * i + 1]);
			glm::vec2 uv2 = glm::vec2(uvs[6 * i + 2], uvs[6 * i + 3]);
			glm::vec2 uv3 = glm::vec2(uvs[6 * i + 4], uvs[6 * i + 5]);
			//Calculations lifted from learnopengl.com
			glm::vec3 edge1 = pos2 - pos1;
			glm::vec3 edge2 = pos3 - pos1;
			glm::vec2 deltaUV1 = uv2 - uv1;
			glm::vec2 deltaUV2 = uv3 - uv1;
			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
			glm::vec3 t;
			t.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			t.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			t.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
			t = glm::normalize(t);
			glm::vec3 bit;
			bit.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			bit.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			bit.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
			bit = glm::normalize(bit);
			//Add for each edge
			for (int j = 0; j < 3; j++) {
				tangents.push_back(t.x);
				tangents.push_back(t.y);
				tangents.push_back(t.z);
				bitangents.push_back(bit.x);
				bitangents.push_back(bit.y);
				bitangents.push_back(bit.z);
			}
		}
		//Pass tangents
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(GLfloat), &tangents[0], GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//Pass bitangents
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, bitangents.size() * sizeof(GLfloat), &bitangents[0], GL_STATIC_DRAW);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}


	// Sets the shininess of the mesh
	void SimpleVAO::setShininess(float shininess) {
		this->shininess = shininess;
	}


	// Sets the texture of the mesh
	void SimpleVAO::setTexture(GLuint texture) {
		this->texture = texture;
	}


	// Sets the specular map of the mesh
	void SimpleVAO::setSpecular(GLuint specular) {
		this->specular = specular;
	}


	// Sets the emission map of the mesh
	void SimpleVAO::setEmission(GLuint emission) {
		this->emission = emission;
	}


	// Sets the normal map of the mesh
	void SimpleVAO::setNormal(GLuint normal) {
		this->normal = normal;
	}
}

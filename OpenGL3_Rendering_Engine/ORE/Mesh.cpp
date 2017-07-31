#include "Mesh.h"


namespace ORE {
	Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<GLuint> textures) {
		this->program = getProgram("singleLight");

		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		//Make sure textures for all types exist
		//Should probably add enums for this
		while (this->textures.size() < 4) {
			this->textures.push_back(0);
		}
		glUseProgram(program);
		glUniform1i(glGetUniformLocation(program, "texture"), 0);
		glUniform1i(glGetUniformLocation(program, "specular"), 1);
		glUniform1i(glGetUniformLocation(program, "normalMap"), 2);
		glUniform1i(glGetUniformLocation(program, "emissionMap"), 3);
		glUseProgram(0);
		shininess = 1;
		setupMesh();
	}


	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}


	void Mesh::draw(World* world) {
		Camera cam = *(world->getCamera());
		//Use correct shaders
		glUseProgram(program);
		//Enable the VAO
		glBindVertexArray(VAO);
		//Pass texture to shaders
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textures[3]);
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
		//Draw the VAO
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}


	void Mesh::setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//Texture coords
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		//Normals
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		//Tangents
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
		//Bitangents
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

		glBindVertexArray(0);
	}
}

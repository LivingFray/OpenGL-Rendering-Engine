#include "SimpleVAO.h"

namespace ORE {
	SimpleVAO::SimpleVAO(GLuint texture, GLuint specular, float shininess){
		//program = getProgram("simpleMesh");
		program = getProgram("singleLight");
		this->texture = texture;
		this->specular = specular;
		this->shininess = shininess;
		glGenVertexArrays(1, &vertexArray);
		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &uvBuffer);
		glGenBuffers(1, &normalBuffer);
		//mvpUniform = glGetUniformLocation(program, "mvp");
	}


	SimpleVAO::~SimpleVAO() {
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteBuffers(1, &normalBuffer);
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
		glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
		//Specular texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular);
		glUniform1i(glGetUniformLocation(program, "specular"), 1);
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
	}
}

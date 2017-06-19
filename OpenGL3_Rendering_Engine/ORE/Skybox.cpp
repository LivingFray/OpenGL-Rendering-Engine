#include "Skybox.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Camera.h"
#include "Engine.h"
namespace ORE {
	Skybox::Skybox() {
		cube = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof vertexData, vertexData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glDisableVertexAttribArray(0);
		program = getProgram("skybox");
		viewUniform = glGetUniformLocation(program, "view");
		projUniform = glGetUniformLocation(program, "projection");
		cubeSampler = glGetUniformLocation(program, "skybox");
	}


	Skybox::~Skybox() {
	}


	void Skybox::draw(Camera camera) const{
		//Only draw if the textures exist
		if (cube) {
			//Set shaders
			glUseProgram(program);
			//Disable depth buffer
			glDepthMask(GL_FALSE);
			glEnableVertexAttribArray(0);
			glBindVertexArray(vertexBuffer);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cube);
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(cubeSampler, 0);
			//Remove translation from camera
			glm::mat4 view = glm::mat4(glm::mat3(camera.getView()));
			glm::mat4 proj = camera.getProjection();
			glUniformMatrix4fv(viewUniform, 1, GL_FALSE, &view[0][0]);
			glUniformMatrix4fv(projUniform, 1, GL_FALSE, &proj[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDisableVertexAttribArray(0);
			//Reenable depth buffer
			glDepthMask(GL_TRUE);
		}
	}

	// Sets the textures of the skybox
	void Skybox::setTextures(const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back) {
		//Delete any old skybox
		if(cube) {
			glDeleteTextures(1, &cube);
			cube = 0;
		}
		glGenTextures(1, &cube);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube);
		int width, height, channels;
		unsigned char* data = nullptr;
		//Right
		data = stbi_load(right, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Left
		data = stbi_load(left, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Top
		data = stbi_load(top, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Bottom
		data = stbi_load(bottom, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Front
		data = stbi_load(front, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Back
		data = stbi_load(back, &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		//Make map seamless
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}
}

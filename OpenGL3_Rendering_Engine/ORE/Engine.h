#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32.lib")

//OpenGL Rendering Engine
namespace ORE {
	extern GLFWwindow* window;
	extern std::map<std::string, GLuint> programs;
	void __sharedInit();
	void init(int width = 800, int height = 600, const char* title = "OpenGL Game", GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);
	void initFullscreen(const char* title = "OpenGL game", GLFWmonitor* monitor = NULL);
	void destroy();
	void setVSync(bool vsync);
	GLuint getProgram(std::string program);
	std::string readFile(std::string filename);
	GLuint loadImage(std::string filename);
};

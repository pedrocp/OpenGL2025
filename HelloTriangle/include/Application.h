#pragma once
#include "glad.h"
#include <string>
#include <map>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	std::map<std::string, GLuint> uniforms;
	
	glm::mat4 projection;
	glm::mat4 camera;
	glm::vec3 eye;
	glm::vec3 center;

	void SetupShaderPassthru();
	void SetupShaderTransforms();
	void SetupShaders();
	void SetupGeometry();
	void SetupGeometrySingleArray();

	float time{0.0f};
	GLuint timeID;
public:
	GLFWwindow* window;
	void Setup();
	void Update();
	void Draw();
	void Keyboard(int key, int scancode, int action, int mods);
};
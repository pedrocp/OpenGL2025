#pragma once
#include "glad.h"
#include <string>
#include <map>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Plane.h"

class Application
{
private:
	std::map<std::string, GLuint> shaders;
	std::map<std::string, GLuint> geometry;
	std::map<std::string, GLuint> uniforms;
	std::map<std::string, GLuint> textures;
	
	glm::mat4 projection;
	glm::mat4 camera;
	glm::mat4 accumTrans;
	glm::vec3 eye;
	glm::vec3 center;

	void SetupShaderPassthru();
	void SetupShaderTransforms();
	void SetupShaders();
	void SetupGeometry();
	void SetupGeometrySingleArray();
	void SetupPlane();
	GLuint SetupTexture(const std::string& filename);

	float time{0.0f};
	float frecuency{17.0f};
	float amplitude{0.125};

	GLuint timeID;
	Plane plane;

public:
	GLFWwindow* window;
	void Setup();
	void Update();
	void Draw();
	void Keyboard(int key, int scancode, int action, int mods);
};
#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>
#include <vector>

void Application::SetupShaders() 
{
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };
	//crear programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shaders compilados" << std::endl;
}
void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f, // vertice 1
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2
	};
	//Crear VAO
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;
	 
	//crear VBO
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER, 
				sizeof(GLfloat) * triangle.size(),
				&triangle[0], 
				GL_STATIC_DRAW);  //Mandamos la geometria al buffer


	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //geometria
	glEnableVertexAttribArray(0);
}

void Application::Setup() 
{
	SetupShaders();
}

void Application::Update() 
{
	//std::cout << "Application::Update()" << std::endl;

}

void Application::Draw() 
{
	//Seleccionar programa (shaders)
	glUseProgram(shaders["passthru"]);
	//Pasar el resto de los parámetros para el programa

	//Seleccionar la geometria (el triangulo)
	glBindVertexArray(geometry["triangulo"]);

	//glDraw()
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::Keyboard() 
{
	std::cout << "Application::Keyboard()" << std::endl;
}
#include "Application.h"
#include "ShaderFuncs.h"
#include <iostream>
#include <vector>
#include "glm/gtc/type_ptr.hpp" 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Application::SetupShaderPassthru()
{
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexPassthru.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentPassthru.glsl") };
	//crear programa
	shaders["passthru"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shaders compilados" << std::endl;

	timeID = glGetUniformLocation(shaders["passthru"], "time");
}

void Application::SetupShaderTransforms()
{
	//cargar shaders
	std::string vertexShader{ loadTextFile("Shaders/vertexTexture.glsl") };
	std::string fragmentShader{ loadTextFile("Shaders/fragmentTexture.glsl") };
	//crear programa
	shaders["transforms"] = InitializeProgram(vertexShader, fragmentShader);
	std::cout << "shaders compilados" << std::endl;

	uniforms["camera"] = glGetUniformLocation(shaders["transforms"], "camera");
	uniforms["projection"] = glGetUniformLocation(shaders["transforms"], "projection");
	uniforms["acumTrans"] = glGetUniformLocation(shaders["transforms"], "accumTrans");
	uniforms["time"] = glGetUniformLocation(shaders["transforms"], "time");
	uniforms["frecuency"] = glGetUniformLocation(shaders["transforms"], "frecuency");
	uniforms["amplitude"] = glGetUniformLocation(shaders["transforms"], "amplitude");
	uniforms["tex0"] = glGetUniformLocation(shaders["transforms"], "tex0");
}

void Application::SetupShaders() 
{
	SetupShaderTransforms();
}

void Application::SetupGeometry()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2

		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2
		1.0f, 1.0f, -1.0f, 1.0f,// vertice 3
	};

	std::vector<GLfloat> colors
	{
		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE

		1.0f, 0.0f, 0.0f, 1.0f, // RED
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE
		1.0f, 1.0f, 1.0f, 1.0f, // WHITE
	};

	//Crear VAO
	GLuint VAO_id, VBO_id, VBO_colorsID;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;
	 
	//crear VBO vertices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER, 
				sizeof(GLfloat) * triangle.size(),
				&triangle[0], 
				GL_STATIC_DRAW);  //Mandamos la geometria al buffer

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //geometria
	glEnableVertexAttribArray(0);

	//crear VBO colores
	glGenBuffers(1, &VBO_colorsID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colorsID);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * colors.size(),
		&colors[0],
		GL_STATIC_DRAW);  //Mandamos la geometria al buffer

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0); //colores
	glEnableVertexAttribArray(1);
}

void Application::SetupGeometrySingleArray()
{
	std::vector<GLfloat> triangle
	{
		-1.0f, 1.0f, -1.0f, 1.0f, // vertice 0
		1.0f, 0.0f, 0.0f, 1.0f, // RED
		-1.0f, -1.0f, -1.0f, 1.0f,// vertice 1
		0.0f, 1.0f, 0.0f, 1.0f, // GREEN
		1.0f, -1.0f, -1.0f, 1.0f, // vertice 2
		0.0f, 0.0f, 1.0f, 1.0f, // BLUE

	};
	{

	//Crear VAO
	GLuint VAO_id, VBO_id;
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);

	geometry["triangulo"] = VAO_id;

	//crear VBO vertices
	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);  //Ojo esto todavia no ha reservado memoria
	//Pasar arreglo de vertices
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GLfloat) * triangle.size(),
		&triangle[0],
		GL_STATIC_DRAW);  //Mandamos la geometria al buffer
	}
	int stride = 8 * sizeof(GLfloat);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0); //geometria
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(4 * sizeof(GLfloat))); //colores
	glEnableVertexAttribArray(1);
}

void Application::SetupPlane()
{
	plane.createPlane(1);
}

GLuint Application::SetupTexture(const std::string& filename)
{
	int width, height, channels;
	unsigned char * img = stbi_load(filename.c_str(), &width, &height, &channels, 4);
	if (img == nullptr)
		return -1;
	
	GLuint texID = -1;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	stbi_image_free(img);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texID;
}

void Application::Setup() 
{
	SetupShaders();
	//SetupGeometry();
	//SetupGeometrySingleArray();
	SetupPlane();
	textures["lenna"] = SetupTexture("Textures/Lenna512x512.png");

	//inicializar camara
	eye = glm::vec3(0.0f, 0.0f, 2.0f);
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	projection = glm::perspective(glm::radians(45.0f), (640.0f / 480.0f), 0.1f, 200.0f);
	accumTrans = glm::rotate(
		glm::mat4(1.0f),
		glm::radians(45.0f),
		glm::vec3(1.0f, 0.0f, 0.0f));

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

void Application::Update() 
{
	//std::cout << "Application::Update()" << std::endl;
	time += 0.0001;

	//actualizar ojo
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	eye = glm::vec3(0.0f, 0.0f, 3.0f);
	//actualizar center
	//actualizar camara
	camera = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Application::Draw() 
{
	//Seleccionar programa (shaders)
	glUseProgram(shaders["transforms"]);
	//Pasar el resto de los parámetros para el programa
	glUniform1f(uniforms["time"], time);
	glUniform1f(uniforms["frecuency"], frecuency);
	glUniform1f(uniforms["amplitude"], amplitude);
	glUniformMatrix4fv(uniforms["camera"], 1, GL_FALSE, glm::value_ptr(camera));
	glUniformMatrix4fv(uniforms["projection"], 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniforms["accumTrans"], 1, GL_FALSE, glm::value_ptr(accumTrans));

	//Seleccionar las texturas
	//texture0
	glBindTexture(GL_TEXTURE_2D, textures["lenna"]);
	glUniform1i(uniforms["tex0"], 0);
	glActiveTexture(GL_TEXTURE0);

	//Seleccionar la geometria (el triangulo)
	//glBindVertexArray(geometry["triangulo"]);
	glBindVertexArray(plane.vao);


	//glDraw()
	glDrawArrays(GL_TRIANGLES, 0, plane.getNumVertex());
}

void Application::Keyboard(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		//activar el flag de salida del probgrama
		glfwSetWindowShouldClose(window, 1);
	}
}
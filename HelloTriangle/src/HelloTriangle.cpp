#include "glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include <iostream>

Application application;

void checkKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        //activar el flag de salida del probgrama
        glfwSetWindowShouldClose(window, 1);
    }
}

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error al inicializar GLAD" << std::endl;
        return -1;
    }

    application.Setup();
    /* Make the window's context current */
    glfwSetKeyCallback(window, checkKeyboard);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        application.Update();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        application.Draw();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
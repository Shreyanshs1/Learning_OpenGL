#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void Run();

private:
    GLFWwindow* window;
    Shader* shader;

    // Buffers
    GLuint VAO_ID;
    GLuint VBO_ID;
    GLuint EBO_ID;

    void InitGL();
    void ProcessInput();
    void CreateTriangle();
};

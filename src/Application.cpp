#include "Application.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <iostream>

Application::Application(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    glViewport(0, 0, width, height);

    shader = new Shader("shaders/default.vert", "shaders/default.frag");
    CreateTriangle();
}

void Application::CreateTriangle() {
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };

    GLuint indices[] = {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
    };

    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


    this->VAO_ID = vao.ID;
    this->VBO_ID = vbo.ID;
    this->EBO_ID = ebo.ID;
    Run();


    vao.Delete();
    vbo.Delete();
    ebo.Delete();

}

void Application::Run() {
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->use();
        glBindVertexArray(VAO_ID);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

Application::~Application() {
    delete shader;
    glfwDestroyWindow(window);
    glfwTerminate();
}


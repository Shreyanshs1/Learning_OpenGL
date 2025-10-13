#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    GLFWwindow* window = glfwCreateWindow(800, 600, "Chota Game Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    // 2.1 unsigned int value to store reference of our vertex shader in(Name it anything you want)
    //in the input we have to specify what type of we want to create i.e. Vertex or Fragment
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Now we have vertex shader now fill it with source that we have copied and pasted above
    //We will use Gl shader source
    //First thing we give it is reference value
    //Second one number of screen we are going to use. In our case it is 1
    //Third we are going to point it to the source code
    //Then last thing doesnt matter

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //Now we have to compile it into machine code so that GPU unserstands it 
    glCompileShader(vertexShader);

    // 2.2 Now do the exact same thing for fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 2.3 Now to actually use both of these, we have to wrap these up into shader program
    //Create a reference value to hold shader program reference
    //We wont give it any value since there is only one type of shader program
    GLuint shaderProgram = glCreateProgram();

    // 2.4 Now to attach the shader program
    //First we give it reference to the shader program and then shader itself
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // 2.5 Now we have to wrap up our shader program
    glLinkProgram(shaderProgram);

    // 2.6 Now we will delete the shader because they are already in th program now, see point 2.4
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // 3.1 We havent done anything with our vertices so nothing will show up on screen
    // Sending stuff between CPU and GPU is slow
    //So, When we send data to the GPU, we try to send data in bunch and it is called buffer



    //3.2 We will now create vertex buffer that will store our vertex data
    // VBO is aktually an array of references, but since we only have one object we only need one
    GLuint VAO ,VBO;

    //Otherwise we can declare it like this  GLuint VBO[5]
    // We can create the buffer like this
    glGenVertexArrays(1, &VAO);// 3.5 make sure to generate VAOs before VBOs

    glGenBuffers(1, &VBO); // First argument is 1 because we only one 3d object and then pass the reference

    glBindVertexArray(VAO); //3.5 Bind VAO

    // 3.3 Binding- binding is concept we make any object our current object
    // so when we fire a function a function that modifies that type of object, it modifies the current object i.e. the binded object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);   //we use gl array buffer cause we need to use that for our vertex buffer

    // 3.4 Now lets actually store our vetices in the buffer
    //Type of data, size of buffer, and data itself(vertices), and finally we specify the use of this data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3.5 VAOs are used to find VBOs and to quickly switch between different VBOs
    // 3.6 Now lets configure VAO
    // Refer LearnOPenGL - Linking Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);






    // Set the color to clear the screen with (a dark blue-ish gray)
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //Clear the color of back buffer with new color
    glClear(GL_COLOR_BUFFER_BIT);
    //swap the back buffer with front buffer to show color on screen
    glfwSwapBuffers(window);


    while (!glfwWindowShouldClose(window)) 
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        processInput(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
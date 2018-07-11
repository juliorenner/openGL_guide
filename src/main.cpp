#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include <string.h>
#include <unistd.h>
// #include <stb_image.h>

#include <iostream>

GLFWwindow* window;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int VBO, VAO, EBO;

int initializeComponents();
void run();
void setupVertexData();
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput();
const char* generatePath(const char* filePath);

int main()
{
    initializeComponents();

    setupVertexData();

    run();

    glfwTerminate();
    return 0;
}

int initializeComponents()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

void run() 
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::string basePath("/home/juliorenner/Documents/git/openGL_guide/src/");
    const char* vertexPath = generatePath("shaders/vertexShader.glsf");
    const char* fragmentPath = generatePath("shaders/fragmentShader.glsf");

    std::cout << vertexPath << std::endl;
    std::cout << fragmentPath << std::endl;

    Shader mainShader(vertexPath, fragmentPath);

    float offSet = 0.0;

    while(!glfwWindowShouldClose(window))
    {
        processInput();

        // sleep(2000);

        glClearColor(0.5f, 0.73f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mainShader.use();
        mainShader.setFloat("offSet", offSet);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

}

void setupVertexData()
{

    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };    

    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,   // first triangle
    // };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);   
}

void processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

const char* generatePath(const char* filePath)
{
    std::string basePath("/home/juliorenner/Documents/git/openGL_guide/src/");
    
    std::string resultPath = basePath + std::string(filePath);

    return resultPath.c_str();
}
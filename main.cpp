#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "includes/Shader.h"
#include "includes/Wall.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 720;

void drawCircle(Shader& shaderProgram)
{
    unsigned int vao, vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float radius = 0.05f;
    int numSegments = 100;
    float segmentAngle = 2.0f * 3.1415926f / numSegments;

    std::vector<float> vertices;
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (int i = 0; i <= numSegments; i++)
    {
        float angle = segmentAngle * i;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
    }

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Define the colors for each section
    std::vector<glm::vec3> colors{
        glm::vec3(0.58f, 0.0f, 0.83f),   // Purple
            glm::vec3(1.0f, 0.0f, 0.0f),   // Red
            glm::vec3(1.0f, 0.50f, 0.0f),   // Orange
            glm::vec3(1.0f, 1.0f, 0.0f),   // Yellow
            glm::vec3(0.0f, 0.5f, 0.0f),   // Green
            glm::vec3(0.0f, 0.0f, 1.0f),   // Blue
            glm::vec3(0.29f, 0.0f, 0.51f)    // Dark purple
    };

    // Draw each section with a different color
    shaderProgram.use();
    for (int i = 0; i < colors.size(); i++)
    {
        glUniform3fv(glGetUniformLocation(shaderProgram.ID, "color"), 1, glm::value_ptr(colors[i]));
        glDrawArrays(GL_TRIANGLE_FAN, i * (numSegments / colors.size()), 54.5);
    }

    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pacman", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Wall bottomWall({ 
        -1.0f, -0.9f, 0.0f,
         1.0f, -0.9f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -0.9f, 0.0f,
         1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f });
    Wall left_bottom_wall({ 
        -1.0f, -0.9f, 0.0f,
        -1.0f, -0.3f, 0.0f,
        -0.9f, -0.9f, 0.0f,
        -1.0f, -0.3f, 0.0f,
        -0.9f, -0.9f, 0.0f,
        -0.9f, -0.3f, 0.0f });
    Wall upWall ({ 
        -1.0f, 1.0f, 0.0f,
         1.0f, 1.0f, 0.0f,
        -1.0f, 0.9f, 0.0f,
         1.0f, 1.0f, 0.0f,
         1.0f, 0.9f, 0.0f,
        -1.0f, 0.9f, 0.0f });

    Wall left_up_wall({
        -1.0f, 0.9f, 0.0f,
        -1.0f, 0.3f, 0.0f,
        -0.9f, 0.9f, 0.0f,
        -1.0f, 0.3f, 0.0f,
        -0.9f, 0.9f, 0.0f,
        -0.9f, 0.3f, 0.0f});

    Wall right_up_wall({
        1.0f, 0.9f, 0.0f,
        1.0f, 0.3f, 0.0f,
        0.9f, 0.9f, 0.0f,
        0.9f, 0.9f, 0.0f,
        1.0f, 0.3f, 0.0f,
        0.9f, 0.3f, 0.0f});
    Wall right_bottom_wall({
        1.0f, -0.9f, 0.0f,
        1.0f, -0.3f, 0.0f,
        0.9f, -0.9f, 0.0f,
        1.0f, -0.3f, 0.0f,
        0.9f, -0.9f, 0.0f,
        0.9f, -0.3f, 0.0f
        });
    Wall left_wall({
        -0.7f,  0.6f, 0.0f,
        -0.7f, -0.6f, 0.0f,
        -0.6f, 0.6f, 0.0f,
        -0.6f, 0.6f, 0.0f,
        -0.7f, -0.6f, 0.0f,
        -0.6f, -0.6f, 0.0f
        });
    Wall right_wall({
        0.7f, 0.6f, 0.0f,
        0.7f, -0.6f, 0.0f,
        0.6f, 0.6f, 0.0f,
        0.6f, 0.6f, 0.0f,
        0.7f, -0.6f, 0.0f,
        0.6f, -0.6f, 0.0f
        });


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        bottomWall.Draw();
        left_bottom_wall.Draw();
        upWall.Draw();
        left_up_wall.Draw();
        right_up_wall.Draw();
        right_bottom_wall.Draw();
        left_wall.Draw();
        right_wall.Draw();
        
        
        drawCircle(shaderProgram);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
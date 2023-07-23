#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "includes/Game.h"
#include "includes/Shader.h"
#include "includes/Wall.h"
#include "includes/pacman.h"

float movementX = 0.0f;
float movementY = 0.0f;
float speed = 0.0005f;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 720;

int main()
{
    Game game(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(game.getWindow());
    glfwSetFramebufferSizeCallback(game.getWindow(), framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Shader pacmanProgram("shaders/pacman_vertex.glsl", "shaders/fragment_shader.glsl");
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
    Pacman pacman;

    // render loop
    // -----------
    while (game.isOpen())
    {
        glm::mat4 transform = glm::mat4(1.0f);
        // input
        // -----
        processInput(game.getWindow());

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "vertexColor"), 0.0f, 0.0f, 1.0f);
        bottomWall.Draw();
        left_bottom_wall.Draw();
        upWall.Draw();
        left_up_wall.Draw();
        right_up_wall.Draw();
        right_bottom_wall.Draw();
        left_wall.Draw();
        right_wall.Draw();
        glUseProgram(0);
        pacmanProgram.use();
        transform = glm::translate(transform, glm::vec3(movementX, 0.0f, 0.0f));
        transform = glm::translate(transform, glm::vec3(0.0f, movementY, 0.0f));
        unsigned int transLoc = glGetUniformLocation(pacmanProgram.ID, "transform");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]/*glm::value_ptr(transform)*/);
        glUniform3f(glGetUniformLocation(pacmanProgram.ID, "vertexColor"), 1.0f, 1.0f, 0.0f);
        pacman.draw();
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(game.getWindow());
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
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        movementX -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        movementX += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        movementY += speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        movementY -= speed;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
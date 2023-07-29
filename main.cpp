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
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 720;
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
int main()
{
    Game game(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(game.getWindow());
    glfwSetFramebufferSizeCallback(game.getWindow(), framebuffer_size_callback);
    glfwSetCursorPosCallback(game.getWindow(), mouse_callback);
    glfwSetScrollCallback(game.getWindow(), scroll_callback);

    glfwSetInputMode(game.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Wall wall;
    std::vector<std::vector<char>> map = {
       { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X' },
       { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
       { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X',' ', 'X' },
       { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X' },
       { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
       { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X' }
    };
    //Mapa 02
    std::vector<std::vector<char>> map2 = {
         { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
         { 'X', ' ', 'X', ' ', 'X', ' ', 'X', 'X', 'X',' ', 'X' },
         { 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X',' ', 'X' },
         { 'X', ' ', 'X', 'X', 'X', ' ', 'X', ' ', ' ',' ', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', 'X', 'X', 'X',' ', 'X' },
         { 'X', 'X', ' ', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
         { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', 'X', ' ', 'X',' ', 'X' },
         { 'X', 'X', ' ', 'X', 'X', ' ', 'X', 'X', ' ',' ', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X',' ', 'X' },
         { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X' },
         { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
         { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X' }
    };

    std::vector<std::vector<std::vector<char>>> maps = { map, map2 };

    // Tamaño de cada celda en el mapa
    float cellSize = 1.0f;
    // Recorrer el mapa y generar las posiciones de los cubos
    std::vector<glm::vec3> cubePositions;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'X')
            {
                float x = static_cast<float>(j) * cellSize;
                float z = static_cast<float>(i) * cellSize;
                cubePositions.push_back(glm::vec3(x, 0.0f, -z)); // Agregar posición al arreglo
            }
        }
    }
    Pacman pacman;
    // render loop
    // -----------
    while (game.isOpen())
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::mat4 model = glm::mat4(1.0f);
        /*glm::mat4 view = glm::mat4(1.0f);*/

        // input
        // -----
        processInput(game.getWindow());

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        shaderProgram.setVec3("vertexColor", glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        glBindVertexArray(wall.getVAO());
        for (const auto& pos : cubePositions)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pos);
            shaderProgram.setMat4("model", model);
            wall.Draw();
        }
        model = glm::translate(model, glm::vec3(movementX, 0.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, movementY));
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        shaderProgram.setMat4("model", model);
        shaderProgram.setVec3("vertexColor", glm::vec3(1.0f, 1.0f, 0.0f));
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
        movementY -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        movementY += speed;
    }
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
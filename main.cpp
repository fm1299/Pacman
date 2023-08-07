#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "includes/Shader.h"
#include "includes/Level.h"
#include "includes/Object.h"
#include "includes/TextRenderer.h"
#include "includes/Game.h"

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 720;
//Movement
float movementX = 0.0f;
float movementZ = 0.0f;
float speed = 0.008f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

//Camera
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Game game(SCR_WIDTH, SCR_HEIGHT);
int main()
{
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Shader shaderProgram("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    Level map1({
       { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X' },
       { 'X', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X' },
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
        },shaderProgram);
    //Mapa 02

    Level map2({
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X','X', 'X' },
        { 'X', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ',' ', ' ', ' ', ' ',' ', 'X' },
        { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', ' ', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', ' ', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', ' ', 'X', ' ',' ', 'X' },
        { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', ' ', ' ', ' ',' ', 'X' },
        { 'X', ' ', 'X', ' ', ' ', ' ', ' ', ' ', 'X',' ', ' ', 'X', ' ',' ', 'X' },
        { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', ' ', ' ', ' ',' ', 'X' },
        { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', 'X', 'X', 'X', ' ', 'X', 'X', 'X',' ', 'X', ' ', 'X',' ', 'X' },
        { 'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', 'X' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','X', 'X', 'X', 'X','X', 'X' },
        },shaderProgram);

    TextRenderer text(SCR_WIDTH, SCR_HEIGHT);
    text.Load("Fonts/OCRAEXT.TTF", 24);
    int level = 0;
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
        // input
        // -----
        processInput(game.getWindow());

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        // camera/view transformation
        glm::mat4 projection = projection = glm::perspective(glm::radians(game.getCam().Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaderProgram.setMat4("projection", projection);
        glm::mat4 view = game.getCam().GetViewMatrix();
        shaderProgram.setMat4("view", view);
        if (level == 0)
        {
            map1.Draw(movementX, movementZ);
            game.getCam().getPos().x = map1.getPacmanPosition().x + movementX;
            game.getCam().getPos().z = map1.getPacmanPosition().z + movementZ + 5.0f;
        }
        else
        {
            map2.Draw(movementX, movementZ);
            game.getCam().getPos().x = map2.getPacmanPosition().x + movementX;
            game.getCam().getPos().z = map2.getPacmanPosition().z + movementZ + 5.0f;
        }
        std::stringstream ss;
        ss << game.getLives();
        text.RenderText("Lives: " + ss.str(), 5.0f, 5.0f, 1.0f);
        //Prueba 
        if (glfwGetKey(game.getWindow(), GLFW_KEY_M) == GLFW_PRESS)
        {
            level = 1;
            movementX = 0.0f;
            movementZ = 0.0f;
        }
        else if (glfwGetKey(game.getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
        {
            level = 0;
            movementX = 0.0f;
            movementZ = 0.0f;
        }
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
        movementZ -= speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        movementZ += speed;
    }
    /*float cameraSpeed = static_cast<float>(2.5 * deltaTime);*/
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        game.getCam().ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        game.getCam().ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        game.getCam().ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        game.getCam().ProcessKeyboard(RIGHT, deltaTime);
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

    game.getCam().ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    game.getCam().ProcessMouseScroll(static_cast<float>(yoffset));
}
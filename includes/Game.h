#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "includes/Camera.h"
class Game
{
private:
	GLFWwindow *window;
	Camera camera;
	int lives;
	int score;
	int screen_width;
	int screen_heigh;
	void initOpengl();
	void initWindow();
public:
	Game(int width, int height);
	GLFWwindow*& getWindow();
	Camera& getCam();
	int getLives();
	bool isOpen();
	~Game();
};
inline void Game::initOpengl()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
inline void Game::initWindow()
{
	this->window = glfwCreateWindow(this->screen_width, this->screen_heigh, "Pacman", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
}

inline Game::Game(int width, int height) : camera(glm::vec3(0.0f, 4.5f, 4.0f)), lives(3), score(0)
{
	this->screen_width = width;
	this->screen_heigh = height;
	this->initOpengl();
	this->initWindow();
}

inline GLFWwindow*& Game::getWindow()
{
	return this->window;
}

inline Camera& Game::getCam()
{
	return this->camera;
}

inline int Game::getLives()
{
	return this->lives;
}

inline bool Game::isOpen()
{
	return !glfwWindowShouldClose(window);
}
inline Game::~Game()
{
}

#endif // !


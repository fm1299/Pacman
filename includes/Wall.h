#ifndef WALL_H
#define WALL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
class Wall
{
private:
	std::vector<float> coordinates;
	void loadData();
	unsigned int VAO;
	unsigned int VBO;
public:
	Wall(std::vector<float> data) : coordinates(data)
	{
		this->VAO = 0;
		this->VBO = 0;
		this->loadData();
	}
	~Wall();
	unsigned int getVAO();
	unsigned int getVBO();
	void Draw();
};

inline unsigned int Wall::getVAO()
{
	return this->VAO;
}
inline unsigned int Wall::getVBO()
{
	return this->VBO;
}
inline void Wall::loadData()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->coordinates.size() * sizeof(float), &this->coordinates[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &this->VBO);
	glDeleteVertexArrays(1, &this->VAO);*/
}
inline void Wall::Draw()
{
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
inline Wall::~Wall()
{
}
#endif

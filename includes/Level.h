#ifndef LEVEL_H
#define LEVEL_H
#include "includes/Wall.h"
#include "includes/Object.h"
class Level
{
private:
	Wall wall;
    Object point;
    Object pacman;
	std::vector<std::vector<char>> map;
    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> pointPositions;
    glm::vec3 pacmanPosition;
    Shader shaderProgram;
public:
	Level(std::vector<std::vector<char>>, Shader& program);
    glm::vec3& getPacmanPosition();
    void Draw(float movementX, float movementY);
	~Level();
};
inline glm::vec3& Level::getPacmanPosition()
{
    return this->pacmanPosition;
}
Level::Level(std::vector<std::vector<char>> pos, Shader& program) : point(0.13), pacman(0.32f)
{
    this->shaderProgram.ID = program.ID;
	this->map = pos;
    float cellSize = 1.0f;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'X')
            {
                float x = static_cast<float>(j) * cellSize;
                float z = static_cast<float>(i) * cellSize;
                this->cubePositions.push_back(glm::vec3(x, 0.0f, -z)); // Agregar posición al arreglo
            }
            else if (map[i][j] == ' ')
            {
                float x = static_cast<float>(j) * cellSize;
                float z = static_cast<float>(i) * cellSize;
                this->pointPositions.push_back(glm::vec3(x, 0.0f, -z));
            }
            else if (map[i][j] == '0')
            {
                float x = static_cast<float>(j) * cellSize;
                float z = static_cast<float>(i) * cellSize;
                this->pacmanPosition.x = x;
                this->pacmanPosition.y = 0.0f;
                this->pacmanPosition.z = -z;
            }
        }
    }

}

void Level::Draw(float movementX, float movementY)
{
    glBindVertexArray(this->wall.getVAO());
    for (const auto& pos : cubePositions)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        this->shaderProgram.setVec3("vertexColor", glm::vec3(0.0f, 0.0f, 1.0f));
        this->shaderProgram.setMat4("model", model);
        wall.Draw();
    }
    for (const auto& pos : pointPositions)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        this->shaderProgram.setMat4("model", model);
        this->shaderProgram.setVec3("vertexColor", glm::vec3(1.0f, 1.0f, 1.0f));
        point.draw();
    }
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->pacmanPosition);
    model = glm::translate(model, glm::vec3(movementX, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, movementY));
    this->shaderProgram.setMat4("model", model);
    this->shaderProgram.setVec3("vertexColor", glm::vec3(1.0f, 1.0f, 0.0f));
    pacman.draw();
}

Level::~Level()
{
}
#endif // !LEVEL_H

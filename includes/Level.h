#ifndef LEVEL_H
#define LEVEL_H
#include "includes/Wall.h"
#include "includes/Object.h"
class Level
{
private:
	Wall wall;
    Object point;
    /*Object pacman;*/
	std::vector<std::vector<char>> map;
    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> pointPositions;
    Shader shaderProgram;
public:
	Level(std::vector<std::vector<char>>, Shader& program);
    void Draw();
	~Level();


};
Level::Level(std::vector<std::vector<char>> pos, Shader& program) : point(0.13)
{
    this->shaderProgram.ID = program.ID;
	this->map = pos;
    // Tamaño de cada celda en el mapa
    float cellSize = 1.0f;
    // Recorrer el mapa y generar las posiciones de los cubos
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
        }
    }

    float cellSize2 = 1.0f;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == ' ')
            {
                float x = static_cast<float>(j) * cellSize2;
                float z = static_cast<float>(i) * cellSize2;
                this->pointPositions.push_back(glm::vec3(x, 0.0f, -z));
            }
        }
    }

}

void Level::Draw()
{
    glBindVertexArray(this->wall.getVAO());
    for (const auto& pos : cubePositions)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
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
}

Level::~Level()
{
}
#endif // !LEVEL_H

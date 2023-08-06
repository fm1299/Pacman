#ifndef LEVEL_H
#define LEVEL_H
#include "Wall.h"

class Level
{
private:
	Wall wall;
	std::vector<std::vector<char>> map;
    std::vector<glm::vec3> cubePositions;
    Shader shaderProgram;
public:
	Level(std::vector<std::vector<char>>, Shader& program);
    void Draw();
	~Level();


};

Level::Level(std::vector<std::vector<char>> pos, Shader& program)
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

}

void Level::Draw()
{
    glBindVertexArray(wall.getVAO());
    for (const auto& pos : cubePositions)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        shaderProgram.setMat4("model", model);
        wall.Draw();
    }
}

Level::~Level()
{
}
#endif // !LEVEL_H

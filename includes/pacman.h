#ifndef PACMAN_H
#define PACMAN_H

class Pacman
{
private:
	std::vector<float> position;
    std::vector<unsigned int> indices;
	void loadData();
	unsigned int VAO;
	unsigned int VBO;
    unsigned int EBO;
public:
	Pacman();
    void draw();
	~Pacman();

};

inline Pacman::Pacman()
{
    this->VAO = 0;
    this->VBO = 0;
    loadData();
}

inline void Pacman::draw()
{
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES,this->indices.size(), GL_UNSIGNED_INT, 0);
}

inline void Pacman::loadData()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glBindVertexArray(this->VAO);
    
    int sectors = 100;
    int stacks = 100;
    float radious = 0.2f;
    for (int i = 0; i <= stacks; ++i)
    {
        float V = i / (float)stacks;
        float phi = V * glm::pi<float>();
        for (int j = 0; j <= sectors; ++j)
        {
            float U = j / (float)sectors;
            float theta = U * (glm::pi<float>() * 2);
            float x = radious * cos(theta) * sin(phi);
            float y = radious * cos(phi);
            float z = radious * sin(theta) * sin(phi);
            this->position.push_back(x);
            this->position.push_back(y);
            this->position.push_back(z);
        }
    }

    // Crear los índices para dibujar la esfera
    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;
        for (int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                this->indices.push_back(k1);
                this->indices.push_back(k2);
                this->indices.push_back(k1 + 1);
            }
            if (i != (stacks - 1))
            {
                this->indices.push_back(k1 + 1);
                this->indices.push_back(k2);
                this->indices.push_back(k2 + 1);
            }
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->position.size() * sizeof(float), this->position.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Pacman::~Pacman()
{
}
#endif
#ifndef OBJECT_H
#define OBJECT_H

class Object
{
private:
	std::vector<float> position;
    std::vector<unsigned int> indices;
    float initialPosX;
    float initialPosY;
	void loadData();
	unsigned int VAO;
	unsigned int VBO;
    unsigned int EBO;
    float radious;
public:
	Object(float rd/*, float posX, float posY*/);
    void draw();
	~Object();

};

inline Object::Object(float rd/*float posX,float posY*/)
{
    this->initialPosX = 0;
    this->initialPosY = 0;
    this->VAO = 0;
    this->VBO = 0;
    this->radious = rd;
    loadData();
}

inline void Object::draw()
{
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES,this->indices.size(), GL_UNSIGNED_INT, 0);
}

inline void Object::loadData()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glBindVertexArray(this->VAO);
    
    int sectors = 100;
    int stacks = 100;
    for (int i = 0; i <= stacks; ++i)
    {
        float V = i / (float)stacks;
        float phi = V * glm::pi<float>();
        for (int j = 0; j <= sectors; ++j)
        {
            float U = j / (float)sectors;
            float theta = U * (glm::pi<float>() * 2);
            float x = this->radious * cos(theta) * sin(phi) + this->initialPosX;
            float y = this->radious * cos(phi);
            float z = this->radious * sin(theta) * sin(phi) + this->initialPosY;
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

Object::~Object()
{
}
#endif
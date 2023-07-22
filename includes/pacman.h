#ifndef PACMAN_H
#define PACMAN_H

class Pacman
{
private:
	std::vector<float> position;
	void loadData();
	unsigned int VAO;
	unsigned int VBO;
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
    glDrawArrays(GL_TRIANGLE_FAN, 1, 135);
}

inline void Pacman::loadData()
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    float radius = 0.05f;
    int numSegments = 135;
    float segmentAngle = 2.0f * 3.1415926f / numSegments;
    this->position.push_back(0.0f);
    this->position.push_back(0.0f);

    for (int i = 0; i <= numSegments; i++)
    {
        float angle = segmentAngle * i;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        this->position.push_back(x);
        this->position.push_back(y);
    }

    glBufferData(GL_ARRAY_BUFFER, this->position.size() * sizeof(float), this->position.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    /*glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);*/
}

Pacman::~Pacman()
{
}
#endif
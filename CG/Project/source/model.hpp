#ifndef MODEL_HPP
#define MODEL_HPP
#include "include.hpp"

class Model
{
private:
    unsigned int vaoId;
    unsigned int vertexCount;
    unsigned int textureId;

public:
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::vec3 position;

    Model();
    Model(const unsigned int, const unsigned int);
    unsigned int getVaoId();
    unsigned int getTextureId();
    void setTexture(const unsigned int);
    void setScale(glm::vec3);
    void setPosition(glm::vec3);
    void setRotation(glm::vec3);
    unsigned int getVertexCount();
    glm::vec3 getPosition()
    {
        return position;
    }
    glm::vec3 getRotation()
    {
        return rotation;
    }
    glm::vec3 getScale(){
        return scale;
    }
    bool increasePosition(const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz, std::vector <Model> modelos);
    void increaseRotation(const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz);
};

#endif
#include "model.hpp"

Model::Model()
{
    vaoId = 0;
    vertexCount = 0;
    textureId = 0;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

bool Model::increasePosition(const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz, std::vector <Model> modelos)
{
//    std::cout << position.x << " " << position.y << " " << position.z << std::endl;
    GLfloat tempx = position.x + t_dx, tempy = position.y + t_dy, tempz = position.z + t_dz;
    glm::vec3 pos, sca;
    bool colisaoX, colisaoY, colisaoZ;
    for(int i = 0; i < modelos.size() - 2; i++){
        pos = modelos.at(i).getPosition();
        sca = modelos.at(i).getScale();
        sca.y = sca.y*3;
        sca.x = sca.x*1.15;
        sca.z = sca.z*1.15;
        colisaoX = tempx + scale.x >= pos.x && pos.x + sca.x >= tempx;
        colisaoY = tempy + scale.y >= pos.y && pos.y + sca.y >= tempy;
        colisaoZ = tempz + scale.z >= pos.z && pos.z + sca.z >= tempz;
        if(colisaoX && colisaoY && colisaoZ) return true;
    }
    position.x += t_dx;
    position.y += t_dy;
    position.z += t_dz;
}

void Model::increaseRotation(const GLfloat t_dx, const GLfloat t_dy, const GLfloat t_dz)
{

    rotation.x += t_dx;
    rotation.y += t_dy;
    rotation.z += t_dz;
}

Model::Model(const unsigned int p_vaoId, const unsigned int p_vertexCount)
{
    vaoId = p_vaoId;
    vertexCount = p_vertexCount;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Model::setPosition(glm::vec3 p_position)
{
    position = p_position;
}

unsigned int Model::getTextureId()
{
    return textureId;
}

void Model::setRotation(glm::vec3 p_rotation)
{
    rotation = p_rotation;
}

void Model::setScale(glm::vec3 p_scale)
{
    scale = p_scale;
}

void Model::setTexture(unsigned int p_textureId)
{
    textureId = p_textureId;
}

unsigned int Model::getVaoId()
{
    return vaoId;
}

unsigned int Model::getVertexCount()
{
    return vertexCount;
}

#include "renderer.hpp"
#include <iostream>

using namespace std;

glm::mat4 createTransformationMatrix(const glm::vec3 t_translation, const glm::vec3 t_rotation, const glm::vec3 t_scale)
{
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, t_translation);
    transform = glm::rotate(transform, glm::radians(t_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // rotation x
    transform = glm::rotate(transform, glm::radians(t_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // rotation y
    transform = glm::rotate(transform, glm::radians(t_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // rotation z
    transform = glm::scale(transform, t_scale);

    return transform;
}
// limpar o buffer com a cor azul ceu
Renderer::Renderer() : backgroundColor(0.5, 0.8, 0.9), shader("./source/vertexShader.glsl", "./source/fragmentShader.glsl")
{

    createProjectionMatrix();
    shader.use();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.setVec3("lightamb", .2f, .2f, .2f);
    shader.setVec3("lightfont", 1.0f, 1.0f, 0.0f);
    shader.setFloat("lightIntensity", 1.0f);
    shader.setVec3("lightPos", 0.0f, 240.0f, .0f);
    shader.stop();
}

void Renderer::createProjectionMatrix()
{

    projectionMatrix = glm::perspective(glm::radians(FOV), (float)800 / (float)600, NEAR_PLANE, FAR_PLANE);
}

void Renderer::render(Camera t_camera, std::vector<Model> models, Player player)
{
    shader.use();
    shader.loadViewMatrix(t_camera);

    prepareModel(player);
    glDrawElements(GL_TRIANGLES, player.getVertexCount(), GL_UNSIGNED_INT, 0);
    unbindModel();

    shader.setVec3("viewPos", t_camera.getPosition());
    for (Model &model : models)
    {
        prepareModel(model);
        glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindModel();
    }

    shader.stop();
}

void Renderer::prepareModel(Model model)
{

    glBindVertexArray(model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTextureId());

    // Model matrix
    shader.setMat4("transform", createTransformationMatrix(model.position, model.rotation, model.scale));
    shader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
}

void Renderer::unbindModel()
{

    // Disable VBOs
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    // Unbind VAO
    glBindVertexArray(0);
}

void Renderer::clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set Background Color
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1);

    glEnable(GL_DEPTH_TEST);
}

void Renderer::cleanUp()
{
    //shader.cleanUp();
}

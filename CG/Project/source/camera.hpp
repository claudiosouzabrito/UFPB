#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include.hpp"
#include <GLFW/glfw3.h>
#include "model.hpp"

class Camera
{

private:
    float distanceCam = 50;
    float anglePlayer;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    bool firstMouse;
    float lastX;
    float lastY;

    float pitch;
    float yaw;
    float roll;

    Model &player;

    float calculateHorizontalDistance()
    {
        return distanceCam * glm::cos(glm::radians(pitch));
    }

    float calculateVerticalDistance()
    {
        return distanceCam * glm::sin(glm::radians(pitch));
    }
    // distanca entre a camera e o objeto

    void calculatePitch(GLFWwindow *window, float yoffset)
    {
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        if (state == GLFW_PRESS)
        {
            float pitchChange = yoffset * 0.1f;
            pitch -= pitchChange;
        }

        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * sin(glm::radians(pitch));
        front = glm::normalize(front);
    }

    void calculateAngleAroundPlayer(GLFWwindow *window, float xoffset)
    {
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS)
        {
            float angleChange = xoffset * 0.3f;
            anglePlayer -= angleChange;
        }
    }
    void calculateCameraPosition(float horizoDistance, float vertexDistance)
    {
        float theta = player.getRotation().y + anglePlayer;
        float offsetX = horizoDistance * sin(glm::radians(theta));
        float offsetz = horizoDistance * cos(glm::radians(theta));
        position.x = player.getPosition().x - offsetX;
        position.z = player.getPosition().z - offsetz;
        position.y = player.getPosition().y + vertexDistance + 5;
    }

public:
    static void calculateZoom(GLFWwindow *window, double xoffset, double yoffset)
    {
        Camera *c = static_cast<Camera *>(glfwGetWindowUserPointer(window));

        float zoomLevel = yoffset * 1;
        c->distanceCam -= zoomLevel;
    }

    void move(GLFWwindow *window)
    {

        GLdouble xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;
        calculatePitch(window, yoffset);
        calculateAngleAroundPlayer(window, xoffset);
        float horizotalDistance = calculateHorizontalDistance();
        float verticalDistance = calculateVerticalDistance();
        calculateCameraPosition(horizotalDistance, verticalDistance);
        yaw = 180 - (player.getRotation().y + anglePlayer);
    }
    Camera(Model &m_player);

    glm::vec3 getPosition();
    float getPitch();
    float getYaw();
    glm::vec3 getFront();
    glm::vec3 getUp();
    void processInput(GLFWwindow *window);
    void handleMouse(GLFWwindow *window);
};

#endif
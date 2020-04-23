#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include "camera.hpp"

//----------------------------------------------------------------------------------------
//FUNCOES REFERENTES A JANELAS
//redimenciona a janela para a viewport
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glwindowhint()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

#endif
#ifndef HEADERS
#define HEADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif


bool checkKeyPress(GLFWwindow *window, int key) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
        return true;
    } else {
        return false;
    }
}
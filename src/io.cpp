#ifndef HEADERS
#define HEADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

void process_input(GLFWwindow *window, int char_code) {
    glfwGetKey(window, char_code);
}
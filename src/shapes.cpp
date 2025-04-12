#ifndef HEADERS
#define HEADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include <cinttypes>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.0f, -0.0f, 0.0f,
    0.5f, 0.5f, 0.5f
}

std::uint32_t VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO); 
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

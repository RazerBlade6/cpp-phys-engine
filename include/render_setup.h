#ifndef HEADERS
#define HEADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include <cinttypes>
#include <string>
#include <iostream>
#include <cmath>

typedef struct {
    std::uint32_t VBO;
    std::uint32_t VAO;
    std::uint32_t EBO;
} renderData;

std::uint32_t setupRenderProgram();
renderData setupRenderObjects();
int renderTriangle(std::uint32_t shaderProgram, renderData data);
int checkRenderStatus(std::uint32_t renderTarget, std::string info);
int checkProgramStatus(std::uint32_t programTarget, std::string info);
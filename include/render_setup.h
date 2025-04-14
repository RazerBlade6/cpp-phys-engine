#ifndef HEADERS
#define HEADERS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include <cinttypes>
#include <string>
#include <iostream>

void setupRendering();
int renderTriangle(std::uint32_t vertexShader, std::uint32_t fragmentShader);
int checkRenderStatus(std::uint32_t renderTarget);
int checkProgramStatus(std::uint32_t programTarget);
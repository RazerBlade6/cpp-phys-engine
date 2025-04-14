#include "render_setup.h"

const char *vertexShaderSrc =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSrc =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void setupRendering() {
    std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!renderTriangle(vertexShader, fragmentShader)) {
        std::cerr << "Failed to Render Triangle" << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int renderTriangle(std::uint32_t vertexShader, std::uint32_t fragmentShader) {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};
    std::uint32_t VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    if (!checkRenderStatus(vertexShader)) {
        return 1;
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    if (!checkRenderStatus(fragmentShader)) {
        return 1;
    }
    std::uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    if (!checkProgramStatus(shaderProgram)) {
        return 1;
    }

    glUseProgram(shaderProgram);
    return 0;
}

int checkRenderStatus(std::uint32_t renderTarget) {
    int success;
    char *infoLog = (char *)malloc(512 * sizeof(char));
    glGetShaderiv(renderTarget, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(renderTarget, 512, NULL, infoLog);
        std::cerr << "Rendering Failed: \n"
                  << infoLog << std::endl;
        return 1;
    }

    free(infoLog);

    return 0;
}

int checkProgramStatus(std::uint32_t programTarget) {
    int success;
    char *infoLog = (char *)malloc(512 * sizeof(char));
    glGetShaderiv(programTarget, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(programTarget, 512, NULL, infoLog);
        std::cerr << "Program Failed: \n"
                  << infoLog << std::endl;
        return 1;
    }

    free(infoLog);

    return 0;
}
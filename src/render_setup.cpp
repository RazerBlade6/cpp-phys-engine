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

int renderTriangle() {
    std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    std::uint32_t indices[] = {
        0, 1, 3
    };
    
    std::uint32_t VBO;
    std::uint32_t EBO;
    std::uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    if (!checkRenderStatus(vertexShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        return 1;
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    if (!checkRenderStatus(fragmentShader)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        return 1;
    }
    std::uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    if (!checkProgramStatus(shaderProgram)) {
        return 1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
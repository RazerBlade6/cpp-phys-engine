#include "render_setup.h"

std::uint32_t setupRenderProgram() {

    std::uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    const char *vertexShaderSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    std::uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSrc =
        "#version 330 core\n"
        "uniform vec4 colour;\n"
        "out vec4 FragColour;\n"
        "void main()\n"
        "{\n"
        "FragColour = colour;\n"
        "}\0";

    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    if (!checkRenderStatus(vertexShader, "VERTEX SHADER:")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    if (!checkRenderStatus(fragmentShader, "FRAGMENT SHADER:")) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    std::uint32_t shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);
    if (!checkProgramStatus(shaderProgram, "SHADER PROGRAM:")) {
        glDeleteProgram(shaderProgram);
        return 0;
    }

    return shaderProgram;
}

renderData setupRenderObjects() {
    float vertices[] = {
        0.0f,  0.5f, 0.75f,
        -0.25f, -0.25f, -0.5f,
       0.25f, -0.25f, -0.5f,
    };

    std::uint32_t indices[] = {
        0, 1, 3,
        0, 1, 2
    };
    
    std::uint32_t VBO;
    std::uint32_t VAO;
    std::uint32_t EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return {VBO, VAO, EBO};
}

int renderTriangle(std::uint32_t shaderProgram, renderData data) {
    glUseProgram(shaderProgram);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int colourLocation = glGetUniformLocation(shaderProgram, "colour");
    float rValue = static_cast<float>(sin(time(NULL) + 2 * M_PI / 3) / 2);
    float gValue = static_cast<float>(sin(time(NULL)) / 2);
    float bValue = static_cast<float>(sin(time(NULL) - 2 * M_PI / 3) / 2);
    glUniform4f(colourLocation, rValue, gValue, bValue, 0.3f);

    glBindVertexArray(data.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 1;
}

int checkRenderStatus(std::uint32_t renderTarget, std::string info) {
    int success;
    char *infoLog = (char *)malloc(512 * sizeof(char));
    glGetShaderiv(renderTarget, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(renderTarget, 512, NULL, infoLog);
        std::cerr << info << "\n"
                  << "Render Failed: \n"
                  << infoLog << std::endl;
        return 0;
    }

    free(infoLog);

    return 1;
}

int checkProgramStatus(std::uint32_t programTarget, std::string info) {
    int success;
    char *infoLog = (char *)malloc(512 * sizeof(char));
    glGetProgramiv(programTarget, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programTarget, 512, NULL, infoLog);
        std::cerr << info << "\n"
                  << "Program Failed: \n"
                  << infoLog << std::endl;
        return 0;
    }

    free(infoLog);

    return 1;
}
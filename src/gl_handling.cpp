//
// Created by noa on 15.03.21.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "gl_handling.hpp"

GL::GL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        isInitialized = false;
        return;
    }

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "out vec2 aColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                     "    aColor = aPos;\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec2 aColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(0.7f, aColor.x, aColor.y, 1.0f);\n"
                                       "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        return;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        return;
    }

    isInitialized = true;
}

bool GL::IsInitialized() const{
    return isInitialized;

}

void GL::render() {
    if (!isInitialized){return;};
    glClearColor(bg.r,bg.g,bg.b,bg.a);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertices);

}

void GL::displayLineLoop(std::vector <glm::vec2> linesLoop) {
    if (!isInitialized){return;};

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(linesLoop), linesLoop.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    vertices = linesLoop.size();

}

void GL::changeBufferSize(unsigned int width, unsigned int height){
    glViewport(0, 0, width, height);
}

void GL::setBackgroundColor(glm::vec4 color){
    bg = color;
}
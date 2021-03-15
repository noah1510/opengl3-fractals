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
                                     "uniform mat4 cameraProjection;\n"
                                     "uniform mat4 cameraZoom;\n"
                                     "uniform mat4 cameraOffset;\n"
                                     "uniform mat4 rotation;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = cameraOffset * cameraProjection * cameraZoom * rotation * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                     "    aColor = vec2((aPos.x+1.0)/2.0,(aPos.y+1.0)/2.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec2 aColor;\n"
                                       "uniform vec3 colorOverlay;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(colorOverlay,1.0f)+vec4(0.0f, aColor.x, aColor.y, 1.0f);\n"
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

    glUseProgram(shaderProgram);

    glm::mat4 cameraProjection = glm::mat4(1.0f);
    int projectionLoc = glGetUniformLocation(shaderProgram, "cameraProjection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

    projectionLoc = glGetUniformLocation(shaderProgram, "cameraZoom");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

    projectionLoc = glGetUniformLocation(shaderProgram, "cameraOffset");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

    projectionLoc = glGetUniformLocation(shaderProgram, "rotation");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));

    isInitialized = true;
}

bool GL::IsInitialized() const{
    return isInitialized;

}

void GL::render() {
    if (!isInitialized){return;};
    glClearColor(bg.r,bg.g,bg.b,bg.a);
    glClear(GL_COLOR_BUFFER_BIT);

    int vertexColorLocation = glGetUniformLocation(shaderProgram, "colorOverlay");
    glUseProgram(shaderProgram);
    glUniform3f(vertexColorLocation, lc.r, lc.g, lc.b);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertices);

}

void GL::displayLineLoop(const std::vector <glm::vec2>& linesLoop) {
    if (!isInitialized){return;};

    vertices = linesLoop.size();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*vertices, linesLoop.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void GL::changeBufferSize(unsigned int width, unsigned int height){
    glViewport(0, 0, width, height);

    glUseProgram(shaderProgram);
    glm::mat4 cameraProjection = glm::ortho(-1.0f, (float)width / (float)height, -1.0f, (float)height / (float)width, -10.0f, 10.0f);
    int projectionLoc = glGetUniformLocation(shaderProgram, "cameraProjection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraProjection));
}

void GL::setBackgroundColor(const glm::vec4& color){
    bg = color;
}

void GL::setLineColorOverlay(const glm::vec3& color){
    lc = color;
}

void GL::setZoom(float zoomFactor){
    glm::mat4 cameraZoom = glm::mat4(1.0);
    cameraZoom = glm::scale(cameraZoom,{zoomFactor,zoomFactor,zoomFactor});
    int projectionLoc = glGetUniformLocation(shaderProgram, "cameraZoom");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraZoom));
}

void GL::setOffset(const glm::vec2& offset){
    glm::mat4 cameraOffset = glm::mat4(1.0);
    cameraOffset = glm::translate(cameraOffset,{offset,0.0f});
    int projectionLoc = glGetUniformLocation(shaderProgram, "cameraOffset");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(cameraOffset));
}

void GL::rotate(float rotGrad){
    glm::mat4 rotation = glm::mat4(1.0);
    rotation = glm::rotate(rotation,rotGrad,{0.0f,0.0f,1.0f});
    int projectionLoc = glGetUniformLocation(shaderProgram, "rotation");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(rotation));
}

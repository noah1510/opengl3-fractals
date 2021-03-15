//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_GL_HANDLING_HPP
#define OPENGL_FRACTALS_GL_HANDLING_HPP

#include "glm/glm.hpp"

#include <vector>
#include <iostream>

class GL{
private:
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int _width = 0;
    unsigned int _height = 0;
    unsigned int vertices = 0;

    bool isInitialized = false;

    glm::vec4 bg = {0.2f, 0.3f, 0.3f, 1.0f};
    glm::vec4 lc = {0.7f, 0.0f, 0.0f, 1.0f};
public:
    GL();
    bool IsInitialized() const;

    void render();
    void displayLineLoop(std::vector<glm::vec2> linesLoop);
    void changeBufferSize(unsigned int width, unsigned int height);
    void setBackgroundColor(glm::vec4 color);
};

#endif //OPENGL_FRACTALS_GL_HANDLING_HPP

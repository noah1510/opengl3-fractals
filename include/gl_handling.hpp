//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_GL_HANDLING_HPP
#define OPENGL_FRACTALS_GL_HANDLING_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

class GL{
private:
    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int vertices = 0;

    bool isInitialized = false;

    glm::vec4 bg = {0.2f, 0.3f, 0.3f, 1.0f};
    glm::vec3 lc = {0.7f, 0.0f, 0.0f};
    glm::vec2 currentOffset = {0.0f,0.0f};
public:
    GL();
    bool IsInitialized() const;

    void render();
    void displayLineLoop(const std::vector<glm::vec2>& linesLoop);
    void changeBufferSize(unsigned int width, unsigned int height);
    void setBackgroundColor(const glm::vec4& color);
    void setLineColorOverlay(const glm::vec3& color);
    void setZoom(float zoomFactor);
    void setOffset(const glm::vec2& offset);
    void rotate(float rotGrad);
    const glm::vec2& getCurrentOffset() const;
};

#endif //OPENGL_FRACTALS_GL_HANDLING_HPP

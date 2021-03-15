//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_HELPER_HPP
#define OPENGL_FRACTALS_HELPER_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class helper{
public:
    static glm::vec2 rotate(glm::vec2 v, float angleDeg){
        glm::mat4 m = glm::mat4(1.0f);
        m = glm::rotate(m,glm::radians(angleDeg),glm::vec3(0.0f,0.0f,1.0f));
        auto v1 = m * glm::vec4(v,1.0,1.0);
        return glm::vec2(v1.x,v1.y);
    }

    static glm::vec2 scale(glm::vec2 v, float scalar){
        glm::mat4 m = glm::mat4(1.0f);
        m = glm::scale(m,glm::vec3{scalar,scalar,scalar});
        auto v1 = m * glm::vec4(v,1.0,1.0);
        return glm::vec2(v1.x,v1.y);
    }
};

#endif //OPENGL_FRACTALS_HELPER_HPP

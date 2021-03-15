//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_FRACTAL_HPP
#define OPENGL_FRACTALS_FRACTAL_HPP

#include "glm/glm.hpp"
#include "gl_handling.hpp"

#include <vector>

class fractal {
protected:
    const static std::vector<glm::vec2> initialLines;

    static std::vector<glm::vec2> step(const std::vector<glm::vec2>& points, unsigned int depth){
        return points;
    }

public:
    static std::vector<glm::vec2> getPoints(unsigned int depth){
        return step(initialLines, depth);
    }

    static void display(GL& renderer, unsigned int depth){
        renderer.displayLineLoop(getPoints(depth));
    }

};


#endif //OPENGL_FRACTALS_FRACTAL_HPP

//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_PEANO_CURVE_HPP
#define OPENGL_FRACTALS_PEANO_CURVE_HPP

#include "glm/glm.hpp"
#include "gl_handling.hpp"

#include "helper.hpp"

#include <vector>

class peano_curve {
protected:
    const static std::vector<glm::vec2> initialLines;

    static std::vector<glm::vec2> step(const std::vector<glm::vec2>& points, unsigned int depth){
        std::vector<glm::vec2> new_points;

        //if not at end of recursion execute recursive
        std::vector<glm::vec2> old_points = depth > 1 ? step(points,depth-1) : points;

        //actually do the fractal thing
        for(unsigned int i = 0; i < old_points.size(); i++){
            glm::vec2 v1 = old_points[i];
            glm::vec2 v2 = old_points[(i+1)%old_points.size()];
            glm::vec2 delta = helper::scale(v2-v1,1.0f/3.0f);
            glm::vec2 delta_r = helper::rotate(delta,-90);
            glm::vec2 delta_l = helper::rotate(delta,90);

            new_points.push_back(v1);
            new_points.push_back(v1+delta);
            new_points.push_back(v1+delta+delta_r);
            new_points.push_back(v1+delta+delta_r+delta);
            new_points.push_back(v1+delta+delta);
            new_points.push_back(v1+delta+delta+delta_l);
            new_points.push_back(v1+delta+delta_l);
            new_points.push_back(v1+delta);
            new_points.push_back(v1+delta+delta);
        }

        return new_points;
    }

public:
    static std::vector<glm::vec2> getPoints(unsigned int depth){
        return depth == 0 ? initialLines : step(initialLines, depth);
    }

    static void display(GL& renderer, unsigned int depth){
        renderer.displayLineLoop(getPoints(depth));
    }

};

#endif //OPENGL_FRACTALS_PEANO_CURVE_HPP

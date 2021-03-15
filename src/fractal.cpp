//
// Created by noa on 15.03.21.
//

#include "fractal.hpp"

const std::vector<glm::vec2> fractal::initialLines = {
        {sqrt(3.0)/2.0, -0.75},
        {-sqrt(3.0)/2.0, -0.75},
        {0.0, 0.75}
};
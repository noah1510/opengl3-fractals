//
// Created by noa on 15.03.21.
//

#include "koch_snowflake.hpp"

const std::vector<glm::vec2> koch_snowflake::initialLines = {
        {sqrt(3.0)/2.0, -0.75},
        {-sqrt(3.0)/2.0, -0.75},
        {0.0, 0.75}
};

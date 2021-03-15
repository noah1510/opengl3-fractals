#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"
#include "gl_handling.hpp"

//fractals
#include "fractal.hpp"
#include "koch_snowflake.hpp"
#include "peano_curve.hpp"

int main (int argc, char * argv[]){
    unsigned int max_depth = 0;
    if(argc > 1){
        max_depth = atoi(argv[1]);
    }

    if(!window::IsInitialized()){
        return -1;
    }

    window::getRenderer().setBackgroundColor({0.0f,0.0f,0.0f,1.0f});
    peano_curve::display(window::getRenderer(),max_depth);
    window::getRenderer().setZoom(0.7f);

    while(!window::shouldClose()){
        float timeValue = glfwGetTime();
        window::getRenderer().setLineColorOverlay({sin(timeValue) / 2.0f + 0.5f,0.0,0.0});
        window::getRenderer().rotate(sin(timeValue)*3.1415);

        window::render();
        window::swapBuffers();
        window::pollEvents();
        window::handleInput();
    }
}

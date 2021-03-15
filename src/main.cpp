#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"
#include "gl_handling.hpp"
#include "fractal.hpp"

int main (){
    if(!window::IsInitialized()){
        return -1;
    }

    window::getRenderer().setBackgroundColor({0.0f,0.0f,0.0f,1.0f});
    fractal::display(window::getRenderer(),0);

    while(!window::shouldClose()){
        float timeValue = glfwGetTime();
        float redValue = sin(timeValue) / 2.0f + 0.5f;
        window::getRenderer().setLineColorOverlay({redValue,0.0,0.0});

        window::render();
        window::swapBuffers();
        window::pollEvents();
        window::handleInput();
    }
}

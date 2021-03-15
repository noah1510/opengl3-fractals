#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"

int main (){
    if(!window::IsInitialized()){
        return -1;
    }

    window::getRenderer().setBackgroundColor({0.0f,0.0f,0.0f,1.0f});
    window::getRenderer().displayLineLoop({{-0.5,-0.3},{0.5,-0.3},{0.0,0.5}});

    while(!window::shouldClose()){
        window::render();
        window::swapBuffers();
        window::pollEvents();
        window::handleInput();
    }
}

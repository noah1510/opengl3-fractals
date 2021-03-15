#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"
#include "gl_handling.hpp"

int main (int argc, char * argv[]){
    unsigned int max_depth = 0;
    if(argc > 1){
        max_depth = atoi(argv[1]);
    }

    if(!window::IsInitialized()){
        return -1;
    }

    window::getRenderer().setBackgroundColor({0.0f,0.0f,0.0f,1.0f});
    window::setFractal(peano,max_depth);
    window::getRenderer().setZoom(0.7f);

    std::cout << "Commands (Buttons to press):" << std::endl;
    std::cout << "  'u' - display koch snowflake" << std::endl;
    std::cout << "  'i' - display peano curve" << std::endl;
    std::cout << "  '0-9' - change render depth" << std::endl;
    std::cout << "  'Esc' - close the program" << std::endl;

    while(!window::shouldClose()){
        float timeValue = glfwGetTime();
        window::getRenderer().setLineColorOverlay({sin(timeValue) / 2.0f + 0.5f,0.0,0.0});
        window::getRenderer().rotate(sin(timeValue/10)*3.1415);

        window::render();
        window::swapBuffers();
        window::pollEvents();
        window::handleInput();
    }
}

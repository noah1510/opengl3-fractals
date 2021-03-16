#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "window.hpp"
#include "gl_handling.hpp"

int main (){
    if(!window::IsInitialized()){
        return -1;
    }

    window::getRenderer().setBackgroundColor({0.0f,0.0f,0.0f,1.0f});
    window::setFractal(koch,4);
    window::getRenderer().setZoom(0.7f);

    std::cout << "Commands (Buttons to press):" << std::endl;
    std::cout << "  'u' - display koch snowflake" << std::endl;
    std::cout << "  'i' - display peano curve" << std::endl;
    std::cout << "  '0-9' - change render depth" << std::endl;
    std::cout << "  '+' - increase render depth" << std::endl;
    std::cout << "  '-' - decrease render depth" << std::endl;
    std::cout << "  'Esc' - close the program" << std::endl;

    while(!window::shouldClose()){
        auto start = std::chrono::system_clock::now();
        float timeValue = glfwGetTime();
        window::getRenderer().setLineColorOverlay({sin(timeValue) / 2.0f + 0.5f,0.0,0.0});
        window::getRenderer().rotate(sin(timeValue/10)*3.1415);

        window::render();
        window::swapBuffers();
        window::pollEvents();
        window::handleInput();
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
        if(diff.count()<0.02){
            std::this_thread::sleep_for(std::chrono::milliseconds( static_cast<int> (20-diff.count()*1000) ) );
        }

    }
}

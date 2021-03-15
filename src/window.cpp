//
// Created by noa on 15.03.21.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.hpp"

window::window(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, "fractals", NULL, NULL);
    if (_window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_window);

    renderer = GL();
    if(!renderer.IsInitialized()){
        _window = nullptr;
        glfwTerminate();
    }

    renderer.changeBufferSize(_width,_height);
    glfwSetFramebufferSizeCallback(_window,window::framebuffer_size_callback);
}

window::~window(){
    glfwTerminate();
}

GL& window::_getRenderer(){
    return renderer;
}

bool window::_shouldClose() {
    return glfwWindowShouldClose(_window);
}

void window::_pollEvents() {
    glfwPollEvents();
}

void window::_swapBuffers() {
    glfwSwapBuffers(_window);
}

bool window::_IsInitialized(){
    return  _window != nullptr && renderer.IsInitialized();
}

void window::_handleInput(){
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {glfwSetWindowShouldClose(_window, true);};
}

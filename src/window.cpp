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

void window::_setFractal(fractal_used frac, unsigned int depth){
    _frac = frac;
    _depth = depth;

    switch(_frac){
        case(koch):
            koch_snowflake::display(renderer,_depth);
            break;
        case(peano):
            peano_curve::display(renderer,_depth);
            break;

        default:
        case(generic):
            fractal::display(renderer,_depth);
            break;
    }
}

void window::_handleInput(){
    if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {glfwSetWindowShouldClose(_window, true);};

    glm::vec2 delta = {0.0,0.0};

    if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS){delta.y = -0.05;};
    if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS){delta.y = 0.05;};
    if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS){delta.x = 0.05;};
    if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS){delta.x = -0.05;};

    renderer.setOffset(renderer.getCurrentOffset()+delta);

    //handle input for fractal selection and depth setting

}

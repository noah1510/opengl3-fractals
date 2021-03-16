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
    fractal_used new_fractal = _frac;
    unsigned int new_depth = _depth;

    if(glfwGetKey(_window, GLFW_KEY_U) == GLFW_PRESS){new_fractal = koch;};
    if(glfwGetKey(_window, GLFW_KEY_I) == GLFW_PRESS){new_fractal = peano;};

    if(glfwGetKey(_window, GLFW_KEY_0) == GLFW_PRESS){new_depth = 0;};
    if(glfwGetKey(_window, GLFW_KEY_1) == GLFW_PRESS){new_depth = 1;};
    if(glfwGetKey(_window, GLFW_KEY_2) == GLFW_PRESS){new_depth = 2;};
    if(glfwGetKey(_window, GLFW_KEY_3) == GLFW_PRESS){new_depth = 3;};
    if(glfwGetKey(_window, GLFW_KEY_4) == GLFW_PRESS){new_depth = 4;};
    if(glfwGetKey(_window, GLFW_KEY_5) == GLFW_PRESS){new_depth = 5;};
    if(glfwGetKey(_window, GLFW_KEY_6) == GLFW_PRESS){new_depth = 6;};
    if(glfwGetKey(_window, GLFW_KEY_7) == GLFW_PRESS){new_depth = 7;};
    if(glfwGetKey(_window, GLFW_KEY_8) == GLFW_PRESS){new_depth = 8;};
    if(glfwGetKey(_window, GLFW_KEY_9) == GLFW_PRESS){new_depth = 9;};

    static auto last_plus = glfwGetKey(_window, PLUS_KEY);
    static auto last_minus = glfwGetKey(_window, MINUS_KEY);

    auto new_plus = glfwGetKey(_window, PLUS_KEY);
    auto new_minus = glfwGetKey(_window, MINUS_KEY);

    if(new_plus != last_plus){
        if (last_plus == GLFW_RELEASE){
            new_depth++;
        }
        last_plus = new_plus;
    };

    if(new_minus != last_minus){
        if (last_minus == GLFW_RELEASE && new_depth != 0){
            new_depth--;
        }
        last_minus = new_minus;
    };

    if (new_fractal != _frac || new_depth != _depth){
        _setFractal(new_fractal,new_depth);
    }

}

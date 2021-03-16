//
// Created by noa on 15.03.21.
//

#ifndef OPENGL_FRACTALS_WINDOW_HPP
#define OPENGL_FRACTALS_WINDOW_HPP

#include <string>
#include <iostream>
#include "GLFW/glfw3.h"
#include "gl_handling.hpp"

#define PLUS_KEY GLFW_KEY_RIGHT_BRACKET
#define MINUS_KEY GLFW_KEY_SLASH

//fractals
#include "fractal.hpp"
#include "koch_snowflake.hpp"
#include "peano_curve.hpp"

enum fractal_used{
    generic = 0,
    koch = 1,
    peano = 2,
};

class window {
private:
    GLFWwindow* _window = nullptr;
    unsigned int _width = 1280;
    unsigned int _height = 720;
    unsigned int _depth = 0;
    fractal_used _frac = koch;
    GL renderer;

    window();
    ~window();
    GL& _getRenderer();
    bool _shouldClose();
    void _swapBuffers();
    void _pollEvents();
    bool _IsInitialized();
    void _handleInput();
    void _setFractal(fractal_used frac, unsigned int depth);

    static window& getInstance(){
        static window instance = window();
        return instance;
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        getInstance()._getRenderer().changeBufferSize(width,height);
        getInstance()._width = width;
        getInstance()._height = height;
    }

public:
    static GL& getRenderer(){
        return getInstance()._getRenderer();
    };

    static bool shouldClose(){
        return getInstance()._shouldClose();
    };

    static void swapBuffers(){
        getInstance()._swapBuffers();
    };

    static void pollEvents(){
        getInstance()._pollEvents();
    };

    static bool IsInitialized(){
        return getInstance()._IsInitialized();
    };

    static void handleInput(){
        return getInstance()._handleInput();
    }

    static void render(){
        getInstance()._getRenderer().render();
    }

    static void setFractal(fractal_used frac, unsigned int depth){
        getInstance()._setFractal(frac,depth);
    }

};


#endif //OPENGL_FRACTALS_WINDOW_HPP

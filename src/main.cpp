#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"

using namespace std;
using namespace glm;

#include "Game.h"
#include "GameObject.h"
#include "GLSL.h"

GLFWwindow *window; // Main application window

int main()
{
    clock_t t;

    if(!glfwInit()){
        cerr << "OpenGL failed to initialize." << endl;
        return -1;
    }

    window = glfwCreateWindow(800, 800, "RESTLESS JUMPER", NULL, NULL);
    if(!window){
        glfwTerminate();
        cerr << "no window." << endl;
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        cerr << "Couldn't initialize GLEW" << endl;
        return -1;
    }

    glGetError();
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    GLSL::checkVersion();
    //VSYNC
    glfwSwapInterval(1);
    //Keyboard Callback
    //glfwSetKeyCallback(window, key_callback);
    //Char Callback
    //glfwSetCharCallback(window, char_callback);
    //Cursor Callback
    //glfwSetCursorPosCallback(window, cursor_position_callback);
    //Mouse Button Callback
    //glfwSetMouseButtonCallback(window, mouse_button_callback);
    //Window Resize Callback
    //glfwSetFramebufferSizeCallback(window, resize_callback);

    Game::Instance().Awake();
    t = clock();
    while(!glfwWindowShouldClose(window)){
        t = clock() - t;
        Game::Instance().Update(t/100.0f);
        // Swap front and back buffers.
        glfwSwapBuffers(window);
        // Poll for and process events.
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
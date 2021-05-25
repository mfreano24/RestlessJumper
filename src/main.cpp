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

/////////////////////////////////////GLFW CALLBACKS/////////////////////////////////////////
static void error_callback(int error, const char *description)
{
    cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //movement inputs
    if(key == GLFW_KEY_D && action == GLFW_PRESS){
        Game::Instance().xInput = 1.0f;
    }
    else if(key == GLFW_KEY_D && action == GLFW_RELEASE){
        Game::Instance().xInput = 0.0f;
    }

    if(key == GLFW_KEY_A && action == GLFW_PRESS){
        Game::Instance().xInput = -1.0f;
    }
    else if(key == GLFW_KEY_A && action == GLFW_RELEASE){
        Game::Instance().xInput = 0.0f;
    }
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow *window, double xmouse, double ymouse)
{
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/////////////////////////////////////MAIN THREAD/////////////////////////////////////////
int main()
{
    clock_t t;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        cerr << "OpenGL failed to initialize." << endl;
        return -1;
    }

    window = glfwCreateWindow(640, 480, "RESTLESS JUMPER", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        cerr << "no window." << endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
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
    glfwSetKeyCallback(window, key_callback);
    //Char Callback
    glfwSetCharCallback(window, char_callback);
    //Cursor Callback
    glfwSetCursorPosCallback(window, cursor_position_callback);
    //Mouse Button Callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    //Window Resize Callback
    glfwSetFramebufferSizeCallback(window, resize_callback);
    Game::Instance().Awake();
    t = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        t = glfwGetTime() - t;
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
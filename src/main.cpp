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

///////////////////////////////////GAME DECLARATIONS////////////////////////////////////////
void Awake()
{
    //initialize the shape, camera, program stuff
    //solid color program for shapes
    cout << "Awake" << endl;
    glfwSetTime(0.0);
    Program *solid_color = new Program();
    string RESOURCE_DIRECTORY = "/../resources/";
    solid_color->setShaderNames(RESOURCE_DIRECTORY + "basic_vert.glsl", RESOURCE_DIRECTORY + "basic_frag.glsl");

    solid_color->setVerbose(true);
    if (solid_color->init())
    {
        solid_color->addAttribute("aPos");
        solid_color->addAttribute("aNor");
        solid_color->addUniform("P");
        solid_color->addUniform("MV");
        solid_color->addUniform("kd");
        solid_color->setVerbose(false);
        cerr << "initialization of program success!" << endl;
    }
    else
    {
        cerr << "initialization of program failed" << endl;
    }
}

void Render()
{
    //this function should render to the screen every frame.

    /*
    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    */
}

void Update(float deltaTime)
{

    //rendering calls
    Render();
}

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
    Awake();
    t = clock();
    while(!glfwWindowShouldClose(window)){
        t = clock() - t;
        cout << "update" << endl;
        Update(t/100.0f);
        // Swap front and back buffers.
        glfwSwapBuffers(window);
        // Poll for and process events.
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
#include <iostream>
#include "Game.h"
using namespace std;

///////////////////////////////////GAME DECLARATIONS////////////////////////////////////////
void Game::Awake()
{
    //initialize the shape, camera, program stuff
    //solid color program for shapes
    time = 0.0f;
    xInput = 0.0f;
    yInput = 0.0f;

    glfwSetTime(0.0);
    Program *solid_color = new Program();
    string RESOURCE_DIRECTORY = "../../resources/";
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

void Game::Render(float deltatime)
{
    //this function should render to the screen every frame.
    float t = glfwGetTime();
    glClearColor(0.6f, 0.6f, 0.6f, 1.0);
    glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //rendering

    for(auto e : objects){
        //render all of the game objects
        e->Draw();
    }
}

void Game::MoveRigidbodies(float deltatime){
    for(auto r : rigidbodies){
        //check collision first
        r->position += deltatime * r->velocity;
    }
}

void Game::Update(float deltatime)
{
    //math stuff, determine next positions of non-static scene objects.
    
    //player position
    if(xInput != 0){
        player->velocity.x = xInput * deltatime;
    }
    
    MoveRigidbodies(deltatime);
    Render(deltatime);
}
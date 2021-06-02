#include <iostream>
#include "Game.h"
#include "MatrixStack.h"
using namespace std;
using namespace glm;
///////////////////////////////////GAME DECLARATIONS////////////////////////////////////////
void Game::Awake()
{
    //initialize the shape, camera, program stuff
    //solid color program for shapes
    time = 0.0f;
    xInput = 0.0f;
    yInput = 0.0f;
    
    glfwSetTime(0.0);

    //projection matrix (orthographic, as this is a 2D game!)
    P = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f);


    shared_ptr<Program> solid_color = make_shared<Program>();
    string RESOURCE_DIRECTORY = "../../resources/";
    solid_color->setShaderNames(RESOURCE_DIRECTORY + "basic_vert.glsl", RESOURCE_DIRECTORY + "basic_frag.glsl");

    solid_color->setVerbose(true);
    if (solid_color->init())
    {
        solid_color->addAttribute("aPos");
        solid_color->addAttribute("aNor");
        solid_color->addAttribute("aTex");
        solid_color->addUniform("P");
        solid_color->addUniform("MV");
        solid_color->addUniform("MV_inv");
        solid_color->addUniform("kd");
        solid_color->setVerbose(false);

        programs["Unlit"]  = solid_color;
        cerr << "initialization of program success!" << endl;
    }
    else
    {
        cerr << "initialization of program failed" << endl;
    }

    //player object
    player = new RigidBody();
    player->color = vec3(0.2, 0.8, 0.8);

    rigidbodies.push_back(player);
    collision.push_back(player);
    objects.push_back(player);


    //scene objects
}

void Game::Render(float deltatime)
{
    
    //this function should render to the screen every frame.
    float t = glfwGetTime();
    glViewport(0, 0, width, height);
    glClearColor(0.6f, 0.6f, 0.6f, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    GLSL::checkError(GET_FILE_LINE);
    //rendering
    MatrixStack* MV = new MatrixStack();
    //cerr << "Objects size: " << objects.size() << endl;
    for(auto e : objects){
        //render all of the game objects
        MV->pushMatrix();
        MV->translate(e->position);
        MV->rotate(e->rotation);
        MV->scale(e->scale);
        if(Game::Instance().programs.find(e->program_name) != Game::Instance().programs.end()){
            e->Draw(MV, Game::Instance().programs[e->program_name]);
        }
        else{
            cerr << "ERROR: shader not registered in the program map!" << endl;
        }
        
        MV->popMatrix();
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
        player->velocity.x = xInput * 10.0f;
    }
    
    MoveRigidbodies(deltatime);
    Render(deltatime);
}
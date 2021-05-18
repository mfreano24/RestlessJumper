#include <iostream>
#include "Game.h"
using namespace std;

void Game::Awake(){
    //initialize the shape, camera, program stuff

}


void Game::Render(){
    //this function should render to the screen every frame.
}

void Game::Update(float deltaTime){
    


    //rendering calls
    Render();
}
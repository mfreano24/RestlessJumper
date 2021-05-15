#include <iostream>
#include "Game.h"
using namespace std;
//init static variables - this way any pointer to a Game* has the same values in the statics?
vector<GameObject*> Game::objects;
vector<Collider*> Game::collision;
vector<Collider*> Game::triggers;
Rigidbody* Game::player;

void Game::Awake(){
    //initialize the shape and camera stuff in here?
}


void Game::Render(){
    //this is where all the rendering will happen, probably.
    //TODO: need to write program/shape classes.
}

void Game::Update(float deltaTime){



    //rendering calls
}
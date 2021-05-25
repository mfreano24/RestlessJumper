#include "GameObject.h"
using namespace std;
using namespace glm;


void GameObject::Draw(/* MatrixStack* M */){
    //use the matrix stack and render the object here
}

void RigidBody::UpdatePosition(float deltatime){
    position += deltatime * velocity;
}
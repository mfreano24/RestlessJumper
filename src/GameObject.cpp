#include "GameObject.h"
#include "Game.h"
using namespace std;
using namespace glm;

void GameObject::Draw(MatrixStack *MV, shared_ptr<Program> prog)
{
    //use the matrix stack and render the object here
    //todo: add support for child game objects here, those will prove useful
    //those can be accomplished by just recursively drawing children.

    //todo: how do i differentiate the programs if they're gonna take different arguments

    if(program_name == "Unlit"){
        prog->bind();
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(Game::Instance().P));
        glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
        glUniformMatrix4fv(prog->getUniform("MV_inv"), 1, GL_FALSE, glm::value_ptr(glm::inverse(glm::transpose(MV->topMatrix()))));
        glUniform3fv(prog->getUniform("kd"), 1, &color[0]);
        shape->draw(prog);
        prog->unbind();
        GLSL::checkError(GET_FILE_LINE);
    }
}

bool Collider::CheckCollision(){
    vector<Collider*> coll = Game::Instance().collision;
    for(auto c : coll){
        //this is a primitive version of our collision testing, where we assume one object is moving and one isn't
        //this also excludes localized testing- if we use a tree later we won't be testing on everything every frame :)
        if(c->name == this->name){
            //don't check collision with ourselves, that'd always return true!
            continue;
        }
        
        //need top left positions
        vec3 A = c->position - vec3(c->x_extent, -c->y_extent, 0.0);
        vec3 B = this->position - vec3(this->x_extent, -this->y_extent, 0.0);

        bool collisionX = A.x + 2 * c->x_extent >= B.x && B.x + 2 * this->x_extent >= A.x;
        bool collisionY = A.y + 2 * c->y_extent >= B.y && B.y + 2 * this->y_extent >= A.y;
        if(collisionX && collisionY){
            return true;
        }
    }
}

void RigidBody::UpdatePosition(float deltatime){
    position += deltatime * velocity;
}



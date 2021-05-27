#include "MatrixStack.h"

#include <stdio.h>
#include <cassert>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;


MatrixStack::MatrixStack(){
    t = new stack<mat4>();
    t->push(mat4(1.0));
}

MatrixStack::~MatrixStack(){}

//TODO: ALL OF THIS

void MatrixStack::pushMatrix(){
    const mat4 &top = t->top();
    t->push(top);
    assert(t->size() <= 50); //dont overdo it, these multiplications take a while

}

void MatrixStack::popMatrix(){
    assert(!t->empty());
    t->pop();
    assert(!t->empty()); //should always at least have the identity matrix on there.
}

void MatrixStack::loadIdentity(){
    glm::mat4 &top = t->top(); //ampersand makes this a reference
    top = glm::mat4(1.0);
}

void MatrixStack::translate(glm::vec3 &xyz){
    glm::mat4 &top = t->top();
    top *= glm::translate(mat4(1.0), xyz);
}

//rotate around some axis by angle degrees.
void MatrixStack::rotate(float angle, glm::vec3 &axis){
    glm::mat4 &top = t->top();
    top *= glm::rotate(glm::mat4(1.0f), angle, axis);
}

void MatrixStack::scale(glm::vec3 &xyz){
    glm::mat4 &top = t->top();
    top *= glm::scale(glm::mat4(1.0f), xyz);
}

mat4 MatrixStack::topMatrix() const{
    return t->top();
}
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

void MatrixStack::pushMatrix(){

}

void MatrixStack::popMatrix(){

}

void MatrixStack::translate(glm::vec3 &xyz){

}
//rotate around some axis by angle degrees.
void MatrixStack::rotate(float angle, glm::vec3 &axis){

}

void MatrixStack::scale(glm::vec3 &xyz){

}

glm::mat4 MatrixStack::topMatrix() const{
    
}
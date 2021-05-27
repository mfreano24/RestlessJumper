#pragma once

#include <stack>
#include <memory>
#include <glm/fwd.hpp>

class MatrixStack{
    private:
    std::stack<glm::mat4>* t;
    public:
    MatrixStack();
    ~MatrixStack();

    void pushMatrix();
    void popMatrix();

    void loadIdentity();
    void translate(glm::vec3& xyz);
    //rotate around some axis by angle degrees.
    void rotate(float angle, glm::vec3& axis);
    void scale(glm::vec3& xyz);

    glm::mat4 topMatrix() const;
};
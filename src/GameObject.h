
#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

const float GRAVITY = -9.81f;

class GameObject{
    public:
    //transform
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    std::string s;
    GameObject(): position(glm::vec3(0)), rotation(glm::vec3(0)), scale(glm::vec3(1)), s("Hello, Static Variables!") {}
    GameObject(glm::vec3& _pos, glm::vec3& _rot, glm::vec3& _sca): position(_pos), rotation(_rot), scale(_sca) {}
    ~GameObject();
};


class Collider : public GameObject{
    //use this like a box collider
    public:
    float x_extent;
    float y_extent;
    bool isTrigger;
    
    Collider(): 
    x_extent(1.0f),
    y_extent(1.0f),
    isTrigger(false),
    GameObject()
    {}

    Collider(glm::vec3 &_pos, glm::vec3 &_rot, glm::vec3 &_sca, float &_x, float &_y, bool _t) :
    x_extent(_x),
    y_extent(_y), 
    isTrigger(_t),
    GameObject(_pos, _rot, _sca)
    {}

    ~Collider();

    bool CheckCollision();
};


class RigidBody : public Collider{
    public:
    glm::vec3 velocity;

    RigidBody():
    velocity(glm::vec3(0)),
    Collider()
    {}

    RigidBody(glm::vec3 &_pos, glm::vec3 &_rot, glm::vec3 &_sca, float &_x, float &_y, bool _t):
    velocity(glm::vec3(0)),
    Collider(_pos, _rot, _sca, _x, _y, _t)
    {}

    ~RigidBody();

    void UpdatePosition();
};

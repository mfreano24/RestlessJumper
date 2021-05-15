#pragma once
#include <vector>

//forward declarations for use in the game class.
class GameObject;
class Collider;
class Rigidbody;


class Game{
    public:
    static std::vector<GameObject*> objects;
    static std::vector<Collider*> collision;
    static std::vector<Collider*> triggers;
    static Rigidbody* player;

    void Render();
    void Awake();
    void Update(float deltaTime);

    Game(){}
    
};
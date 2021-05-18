#pragma once
#include <vector> 
#include "Program.h"
//forward declarations for use in the game class.
class GameObject;
class Collider;
class Rigidbody;


enum class Game_State{ STARTUP, GAMEPLAY, GAME_WIN };

class Game{
    public:
    static Game &Instance()
    {
        static Game m_instance; //properly instantiated on first use, destroyed on 2nd and after.
        return m_instance;
    }

    private:
    Game() {}

    public:
    //ensure that no copies ever get made.
    Game(Game const &) = delete;
    void operator=(Game const &) = delete;
    std::vector<GameObject*> objects;
    std::vector<Collider*> collision;
    std::vector<Collider*> triggers;
    std::map<string, Program*> programs;
    Game_State state;
    Rigidbody* player;

    void Render();
    void Awake();
    void Update(float deltaTime);
    
};
#pragma once
#include <vector>
#include <map>

#include "Program.h"
#include "GLSL.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"


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
    int width, height;
    std::vector<GameObject*> objects;
    std::vector<Collider*> collision;
    std::vector<RigidBody*> rigidbodies; //non player rigidbodies
    RigidBody* player; //NOTE: this pointer should go in the vector above as well so that MoveRigidbodies moves it in scene.
    std::vector<Collider*> triggers;
    std::map<std::string, std::shared_ptr<Program>> programs;
    Game_State state;
    glm::mat4 P; //should be the same for everyone
    float time;
    float xInput, yInput;

    void Awake();
    void MoveRigidbodies(float deltatime);
    void Update(float deltatime);
    void Render(float deltatime);
};

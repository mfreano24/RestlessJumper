#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <time.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"

using namespace std;
using namespace glm;

#include "Game.h"
#include "GameObject.h"

int main()
{
    
    clock_t t;

    Game::Instance().Awake();
    t = clock();
    int TESTER = 10000;
    while(TESTER--){
        t = clock() - t;
        Game::Instance().Update(t/100.0f);
    }

    cout << t/100 << endl;

}
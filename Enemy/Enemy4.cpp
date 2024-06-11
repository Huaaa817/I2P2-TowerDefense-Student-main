#include <allegro5/base.h>
#include <random>
#include <string>
#include <Engine/LOG.hpp>

#include "Engine/Point.hpp"
#include "Enemy4.h"

Enemy4::Enemy4(int x, int y) : Enemy("play/enemy-4.png", x, y, 20, 30, 100, 50, 40){}

void Enemy4::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    timeElapsed+=deltaTime;
    bool filp=false;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0f, 1.0f);
    float rnd = dist(rng);

    if (rnd < 0.5f) { // 50%
        speedUp = !speedUp;
        filp=true;
    }
    if (timeElapsed >= 2.0) {
        if (speedUp && filp && speed<40) {
            //Engine::LOG(Engine::DEBUGGING) << speedUp;
            speed+=10;
        } else if(!speedUp && filp && speed>20){
            //Engine::LOG(Engine::DEBUGGING) << speedUp;
            speed-=10;
        }
        //speedUp = !speedUp; // 切换标志
        timeElapsed = 0.0; // 重置计时器
    }

}

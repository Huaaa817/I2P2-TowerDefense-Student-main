#ifndef ENEMY4_HPP
#define ENEMY4_HPP
#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class Enemy4 : public Enemy {

public:
    Enemy4(int x, int y);
    void Update(float deltaTime) override;
    float timeElapsed=0.0;
    bool speedUp =true;
};
#endif // ENEMY4_HPP

#ifndef BULLET4_H
#define BULLET4_H
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class Bullet4 : public Bullet {
public:
    explicit Bullet4(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
    void Update(float deltaTime) override;
};

#endif //BULLET4_H

#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "Bullet4.h"

#include "Engine/Collider.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Turret;

Bullet4::Bullet4(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
    Bullet("play/bullet-4.png", 700, 5, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void Bullet4::OnExplode(Enemy* enemy) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

void Bullet4::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    PlayScene* scene = getPlayScene();
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto& it : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(it);
        if (!enemy->Visible)
            continue;
        if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
            OnExplode(enemy);
            enemy->Hit(damage);
            getPlayScene()->BulletGroup->RemoveObject(objectIterator);
            return;
        }
    }
    // Check if out of boundary.
    if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize()))
        if (!Bounced) {

            Velocity.x=-Velocity.x;
            Velocity.y=-Velocity.y;
            Bounced=true;
            Position.x += Velocity.x * deltaTime;
            Position.y += Velocity.y * deltaTime;

        }
        else getPlayScene()->BulletGroup->RemoveObject(objectIterator);
}
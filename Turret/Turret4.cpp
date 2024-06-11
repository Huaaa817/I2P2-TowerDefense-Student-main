#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet4.h"
#include "Engine/Group.hpp"
#include "Turret4.h"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int Turret4::Price = 100;
Turret4::Turret4(float x, float y) :
    // TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'MachineGunTurret.hpp', 'MachineGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/turret-4.png", x, y, 200, Price, 1.7) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Turret4::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Bullet4(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}

#ifndef TURRET4_H
#define TURRET4_H

#include "Turret.hpp"

class Turret4: public Turret {
public:
    static const int Price;
    Turret4(float x, float y);
    void CreateBullet() override;
};

#endif //TURRET4_H

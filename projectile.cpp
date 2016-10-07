//
// Created by Frederik on 07/06/2016.
//

#include "projectile.h"
namespace game_Core {
    projectile::projectile(float x, float y, float w, float h, int type, float destX, float destY) : Entity(x, y, w, h, type, false) {
        this->destY = destY;
    }

    void projectile::move(float x, float y) {
        this->x += x;
        this->y += y;
        if ((this->y < destY + 1 && this->y > this->destY - 1)) {
            this->type = 5;
        }
    }
}






#include "Enemy.h"
namespace game_Core {
    Enemy::Enemy(float x, float y, float w, float h, int type, bool dir) : Entity(x, y, w, h, type, dir) {

    }
    void Enemy::move(float x, float y) {
        if (!dir) this->x += x;
        else if (dir) this->x -= x;
    }
}




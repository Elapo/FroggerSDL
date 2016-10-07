//
// Created by Frederik on 29/02/2016.
//

#include "Player.h"
namespace game_Core {
    Player::Player(float x, float y, float w, float h, int type, settings* set) : Entity(x, y, w, h, type, false) { //player should never be flipped
        this->set = set->getSettings();
    }

    void Player::move(float x, float y) {
        if (y < 0 && this->y + y >= 0) {
            this->y += y;
        }
        else if (y > 0 && this->y + y <= (this->set->gridSize - 2)) {
            this->y += y;
        }

        if (x < 0 && this->x + x >= 0) {
            this->x += x;
        }
        else if (x > 0 && this->x + x <= 95) {
            this->x += x;
        }
    }
}











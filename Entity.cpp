//
// Created by Frederik on 17/03/2016.
//

#include "Entity.h"
namespace game_Core {
    Entity::Entity(float x, float y, float w, float h, int type, bool dir) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->type = type;
        this->dir = dir;
    }

    int Entity::getXco() {
        return (int) x;
    }

    int Entity::getYco() {
        return (int) y;
    }

    void Entity::setCo(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int Entity::getType() {
        return type;
    }

    void Entity::flip() {
        this->dir = !this->dir;
    }
}




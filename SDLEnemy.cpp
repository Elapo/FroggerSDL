//
// Created by Frederik on 29/02/2016.
//

#include "SDLEnemy.h"
namespace game_SDL {
    SDLEnemy::SDLEnemy(float x, float y, float w, float h, int type, SDL_Texture *t, Renderer *r, bool fliph) : Enemy(x, y, w, h, type, fliph) {
        this->r = r;
        texture = t;
    }

    void SDLEnemy::Draw() {
        r->render(x, y, w, h, texture, dir);
    }

    SDLEnemy::~SDLEnemy() {
        delete (r);
        SDL_DestroyTexture(texture);
    }
}




//
// Created by Frederik on 07/06/2016.
//

#include "SDLProjectile.h"
namespace game_SDL {
    SDLProjectile::SDLProjectile(float x, float y, float w, float h, int type, float destX, float destY, SDL_Texture *t,
                                 Renderer *r) : projectile(x, y, w, h, type, destX, destY) {
        this->texture = t;
        this->r = r;
    }

    SDLProjectile::~SDLProjectile() {
        SDL_DestroyTexture(texture);
        delete (r);
    }

    void SDLProjectile::Draw() {
        r->renderParticle(this->x, this->y, this->w, this->h, this->texture);
    }
}






//
// Created by Frederik on 07/06/2016.
//

#ifndef FROGGERSDL_SDLPROJECTILE_H
#define FROGGERSDL_SDLPROJECTILE_H


#include <SDL2/SDL_render.h>
#include "Renderer.h"
#include "projectile.h"
using namespace game_Core;
namespace game_SDL {
    /*!
     * Class containing the SDL implementation of projectile
     * */
    class SDLProjectile : public projectile {
    public:
        /*! Constructor
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param destX float, end point of projectile, X value
         * \param destY float, end point of projectile, Y value
         * \param t SDL_Texture*, pointer to texture for Enemy
         * \param r Renderer*, pointer to renderer
         * */
        SDLProjectile(float x, float y, float w, float h, int type, float destX, float destY, SDL_Texture *t, Renderer *r);
        ~SDLProjectile();
        void Draw();

    private:
        SDL_Texture *texture;/*!< Texture*/
        Renderer *r;/*!< Renderer, to draw the Entity*/
    };
}


#endif //FROGGERSDL_SDLPROJECTILE_H

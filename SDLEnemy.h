//
// Created by Frederik on 29/02/2016.
//

#ifndef FROGGERSDL_SDLENEMY_H
#define FROGGERSDL_SDLENEMY_H

#include <SDL2/SDL_render.h>
#include "Enemy.h"
#include "Renderer.h"
using namespace game_Core;
namespace game_SDL {
    /*!
     * Class containing the SDL implementation of Enemy
     * */
    class SDLEnemy : public Enemy {
    public:
        /*! Constructor
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param t SDL_Texture*, pointer to texture for Enemy
         * \param fliph bool, used to change direction and mirror sprite
         * */
        SDLEnemy(float x, float y, float w, float h, int type, SDL_Texture *t, Renderer *r, bool fliph);
        ~SDLEnemy();
        void Draw();

    private:
        SDL_Texture *texture;/*!< Texture*/
        Renderer *r;/*!< Renderer, to draw the Entity*/
    };
}
#endif //FROGGERSDL_SDLENEMY_H
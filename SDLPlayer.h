//
// Created by Frederik on 29/02/2016.
//


#ifndef FROGGERSDL_SDLPLAYER_H
#define FROGGERSDL_SDLPLAYER_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "Player.h"
#include "Renderer.h"
#include "SDLFactory.h"
#include "SDLProjectile.h"
using namespace game_Core;
namespace game_SDL {
    class SDLFactory; //incomplete type because cyclic dependency (SDLFactory needs SDLPlayer and vice versa)
    /*!
     * Class containing the SDL implementation of Player
     * */
    class SDLPlayer : public Player {
    public:
        /*! Constructor
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param t SDL_Texture*, pointer to texture for Enemy
         * \param r Renderer*, pointer to renderer
         * \param f SDLFactory* pointer to SDLFactory
         * \param set settings, Class containing settings read from configuration file
         * */
        SDLPlayer(float x, float y, float h, float w, int type, SDL_Texture *t, Renderer *r, SDLFactory *f, settings* set);
        ~SDLPlayer();
        void Draw();
        /*!
         * Uses SDLFactory to create a bullet originating from original position
         */
        projectile *Shoot();
        /*!
         * Makes the controller vibrate.
         * \param ms int, lenght of vibration
         */
        void rumble(int ms);
        int getInput();

    private:
        SDL_Event e; /*!< Event to catch keyboard/mouse/controller actions*/
        SDL_Texture *texture;/*!< Texture*/
        Renderer *r;/*!< Renderer, to draw the Entity*/
        SDLFactory *f;/*!< SDLFactory for the creation of projectiles*/
        SDL_GameController* gameController = NULL;/*!< The game controller, if connected*/
        SDL_Haptic* haptic;/*< Handler voor force feedback*/
    };
}
#endif //FROGGERSDL_SDLPLAYER_H
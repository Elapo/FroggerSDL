//
// Created by Frederik on 29/02/2016.
//

#ifndef FROGGERSDL_SDLFACTORY_H
#define FROGGERSDL_SDLFACTORY_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include "SDLEnemy.h"
#include "SDLPlayer.h"
#include "AbstractFactory.h"
#include "Renderer.h"
#include "projectile.h"
using namespace game_Core;
namespace game_SDL {
    class SDLFactory : public AbstractFactory {
    public:
        /*!
         * Constructor.
         * \param s settings, Class containing settings read from configuration file
         */
        SDLFactory(settings *s);
        //! Destructor
        ~SDLFactory();
        /*!
         * \param lane int lane to spawn enemy in
         * \return SDLEnemy
         */
        Enemy *createEnemy(int lane);
        /*!
         * Spawns the player
         * \return SDLPlayer
         */
        Player *createPlayer();
        /*!
         * Spawns a healthpack
         * \param lane int lane to spawn Healthpack in
         * \return SDLEnemy
         */
        Enemy *createHealthPack(int lane);
        /*!
         * spawns an ammopack
         * \param lane int lane to spawn enemy in
         * \return SDLEnemy
         */
        Enemy *createAmmoPack(int lane);
        /*!
         * spawns a projectile
         * \param startX float, X position to start at.
         * \param startY int, Y position to start at.
         * \param destX float, end point X value
         * \param destY float, end point Y value
         * \return SDLProjectile
         */
        projectile *createProjectile(float startX, int startY, float destX, float destY);
        /*!
         * Creates renderer and makes it load all media
         * \return status
         */
        int init();
        /*!
         * Calls renderer::update()
         */
        void update();
        /*!
         * Calls renderer::endUpdate()
         */
        void endUpdate();
        /*!
         * Closes renderer and deletes all vars.
         */
        void close();
        /*!
         * Creates a new FPS regulator
         * \param cap int, framerate to cap at
         * \return SDLFPSReg
         */
        FPSReg *createFPSRegulator(int cap);
        /*!
         * Calls renderer::renderText()
         * \param x float, X position of text on grid
         * \param y float, Y position of text on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param text string, contains new text
         */
        void renderText(float x, float y, float w, float h, string text);
        /*!
         * Calls renderer.playFX()
         * \param fx int, id of fx to play
         */
        void playFX(int fx);

    private:
        /*!
         * Calculates the width so the aspect ratio stays the same
         */
        float calc_width(int scrnh, int w, int h);
        Renderer *r = NULL;/*!< Renderer*/
        settings* s;/*!<Contains all settings*/
        SDL_Texture *playerSprite = NULL;/*!<Player texture*/
        SDL_Texture *enemySprite = NULL;/*!<Enemy texture*/
        SDL_Texture *healthPackSprite = NULL;/*!<Healthpack texture*/
        SDL_Texture *ammoPackSprite = NULL;/*!<AmmoPack texture*/
        SDL_Texture *projSprite = NULL;/*!<Projectile texture*/
    };
}
#endif //FROGGERSDL_SDLFACTORY_H
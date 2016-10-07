//
// Created by Frederik on 29/02/2016.
//

#ifndef FROGGERSDL_PLAYER_H
#define FROGGERSDL_PLAYER_H

#include "Entity.h"
#include "projectile.h"
#include "settings.h"
using namespace game_settings;
namespace game_Core {
    class Player : public Entity {
    public:
        /*!
         * Constructor.
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param set settings, Class containing settings read from configuration file
         */
        Player(float x, float y, float w, float h, int type, settings* set);
        //! Destructor
        virtual ~Player() { };
        /*!
         * Retrieve input.
         * \return int in the form of a KeyNames member
         */
        virtual int getInput() = 0;
        /*!
         * Fires a projectile
         * \return projectile
         */
        virtual projectile *Shoot() = 0;
        /*!
         * Makes the controller vibrate.
         * \param ms int, lenght of vibration
         */
        virtual void rumble(int ms) = 0;
        void move(float x, float y);

    private:
        techSetting* set;/*!<Technical settings*/
    };
}
#endif //FROGGERSDL_PLAYER_H


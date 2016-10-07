#ifndef FROGGERSDL_ENEMY_H
#define FROGGERSDL_ENEMY_H

#include "Entity.h"
namespace game_Core {
//! Enemy class
/*!
 * Base class for Enemy
 */
    class Enemy : public Entity {
    public:
        /*! Constructor
         * \param x float, X position of enemy on grid
         * \param y float, Y position of enemy on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param dir bool, used to change direction and mirror sprite
         * */
        Enemy(float x, float y, float w, float h, int type, bool dir);
        //! Destructor
        virtual ~Enemy() { };
        void move(float x, float y);
    };
}
#endif //FROGGERSDL_ENEMY_H
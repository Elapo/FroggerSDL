//
// Created by Frederik on 07/06/2016.
//

#ifndef FROGGERSDL_PROJECTILE_H
#define FROGGERSDL_PROJECTILE_H


#include "Entity.h"
namespace game_Core {
    /*!
     * Class for projectiles
     */
    class projectile : public Entity {
    public:
        /*! Constructor
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param destX float, end point of projectile, X value
         * \param destY float, end point of projectile, Y value
         * */
        projectile(float x, float y, float w, float h, int type, float destX, float destY);
        //! Destructor
        ~projectile() { };
        void move(float x, float y);

    protected:
        float destY; /*! Y destination of projectile. X is not used in this case*/
    };
}


#endif //FROGGERSDL_PROJECTILE_H

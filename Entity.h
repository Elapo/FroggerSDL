

#ifndef FROGGERSDL_ENTITY_H
#define FROGGERSDL_ENTITY_H

namespace game_Core {
//! Entity class
/*!
 * Base class for Enemy, Player and projectile
 */
    class Entity {
    public:
        /*! Constructor
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param type int, type identifier, 0 for enemy, 1 for Player, 2 and 3 for power ups, 4 for particles and 5 for expired particles.
         * \param dir bool, used to change direction and mirror sprite
         * */
        Entity(float x, float y, float w, float h, int type, bool dir);
        //! Destructor
        virtual ~Entity() { };
        /*!
         * \return Current X value on grid
         */
        int getXco();
        /*!
         * \return Current Y value on grid
         */
        int getYco();
        /*!
         * Method to set the coordinates of the Entity.
         * \param x int, X value on grid
         * \param y int, Y value on grid
         */
        void setCo(int x, int y);
        /*!
         * \return The type of the Entity
         */
        int getType();
        /*!
         * Flips the sprite by flipping boolean dir
         */
        void flip();
        /*!
         * Moves the Entity.
         * \param x float, value to move in x
         * \param y float, value to move in y
         */
        virtual void move(float x, float y) = 0;
        /*!
         * Draw entity on screen. Should be called in the correct order, after update() & before endUpdate()
         */
        virtual void Draw() = 0;

    protected:
        float x, y, h, w;/*!< The Entity's coordinates*/
        int type;/*!< Entity's Type */
        bool dir;/*!< Entity's direction*/
    };
}

#endif //FROGGERSDL_ENTITY_H

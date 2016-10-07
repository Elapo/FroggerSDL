//
// Created by Frederik on 29/02/2016.
//

#ifndef FROGGERSDL_GAMEOBJECT_H
#define FROGGERSDL_GAMEOBJECT_H
#include "AbstractFactory.h"
#include <vector>
#include "Entity.h"
#include "settings.h"
#include <time.h>

using namespace std;
using namespace game_settings;
namespace game_Core {
    /*!
     * Class containing main game logic
     */
    class GameObject {
    public:
        /*!
         * Constructor
         * \param AF Abstractfactory to create classes
         * \param s settings, Class containing settings read from configuration file
         */
        GameObject(AbstractFactory *AF, settings *s);
        //! Destructor
        ~GameObject();
        /*!
         * initialize variables and create initial objects
         * \return status
         */
        int init();
        /*!
         * Main game loop
         * \return status
         */
        int loop();

    private:
        /*!
         * \return a random lane 1-7, leaving out 4
         */
        int getLane();
        /*!
         * \return a random value to be added to the initial position of enemies
         */
        int getRandomX();
        /*!
         * \param e Entity to check for collision
         * \param p Entity to check for collision with
         * \returns true if Entities collide
         */
        bool checkCollision(Entity *e, Entity *p);
        /*!
         * Resets all enemies into random lanes/positions
         */
        void resetEnemies();
        /*!
         * \param e entity to set to a random position
         */
        void setEnemyRandomPos(Entity *e);
        /*!
         * Kill the player and reset cars or handle game over
         */
        void killPlayer();
        /*!
         * Update the text with new values
         */
        void updateText();
        /*!
         * Add a level to current, reset all cars and spawn extra
         */
        void levelUp();
        /*!
         * \param amount Amount of cars that need to spawn
         */
        void spawnCars(int amount);
        /*!
         * Tries to remove overlapping cars by moving them
         */
        void removeCarOverlap();
        /*!
         * \param particle to check
         * Check for a collision with a particle
         * \return position of colliding object in vector
         */
        int checkParticleCollision(Entity *particle);
        /*!
         * Check whether cars are overlapping
         * \param e Entity car 1
         * \param p Entity car 2
         * \return true if overlapping
         */
        bool checkCarOverlap(Entity *e, Entity *p);

        AbstractFactory *aFact;/*!<SDLFactory that handles all the spawning*/
        Player *player;/*!< SDLPlayer*/
        FPSReg *regulator;/*!< Framerate regulator*/
        settings* s;/*!< Contains all settings*/
        bool quit = false;/*!< bool to quit main loop*/
        vector<Entity *> entities/*!<Contains pointer ro every entity currently on the screen*/;
        int score = 0, level = 1, lives = 3, currEnemies, ammo;/*!< Game variables*/
        float enemySpeed, pickupSpeed;/*!< movement speed of enemy & pickups*/
        clock_t start, current;/*!< variables for timer*/
        double elapsed;/*!<Variable to store the time difference*/
    };
}
#endif //FROGGERSDL_GAMEOBJECT_H
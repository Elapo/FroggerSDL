
#ifndef FROGGERSDL_ABSTRACTFACTORY_H
#define FROGGERSDL_ABSTRACTFACTORY_H

#include "Player.h"
#include "Enemy.h"
#include "FPSReg.h"
#include "settings.h"
#include "projectile.h"
#include <string>
using namespace std;
namespace game_Core {
//!AbstractFactory Class
/*!
 Abstract class containing all of the virtual functions needed to communicate with
 SDL code. See SDLFactory for member descriptions
 */
    class AbstractFactory {
    public:
        virtual void close() = 0;
        virtual void update() = 0;
        virtual void endUpdate() = 0;
        virtual int init() = 0;
        virtual void renderText(float x, float y, float w, float h, string text) = 0;
        virtual Player *createPlayer() = 0;
        virtual Enemy *createEnemy(int lane) = 0;
        virtual Enemy *createHealthPack(int lane) = 0;
        virtual FPSReg *createFPSRegulator(int cap) = 0;
        virtual Enemy *createAmmoPack(int lane) = 0;
        virtual projectile *createProjectile(float startX, int startY, float destX, float destY) = 0;
        virtual void playFX(int fx) = 0;
    };
}
#endif //FROGGERSDL_ABSTRACTFACTORY_H
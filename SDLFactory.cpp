//
// Created by Frederik on 29/02/2016.
//

#include "SDL2/SDL_Image.h"
#include "SDLFPSReg.h"
#include "SDLFactory.h"
#include "SDLProjectile.h"

using namespace game_settings;
namespace game_SDL {
    SDLFactory::SDLFactory(settings* s) {
        this->s = s;
    }

    SDLFactory::~SDLFactory() {
        delete (r);
    }

    Enemy *SDLFactory::createEnemy(int lane) {
        bool flip = false;
        SDL_Surface *carSprite;
        if (enemySprite == NULL) {
            carSprite = IMG_Load(s->getSettings()->spriteCar1.c_str());
            if (carSprite != NULL) {
                enemySprite = r->createTexture(carSprite);
            }
        }
        float xStart, wStart, yStart = lane;
        wStart = calc_width(s->getSettings()->screenHeight, s->getSettings()->spriteCarW, s->getSettings()->spriteCarH);
        if (lane > 3) {
            yStart++;
            xStart = 105.0f; //percentage
            flip = true;
        }
        else {
            xStart = -15.0f;
        }
        return new SDLEnemy(xStart, yStart, (wStart * 0.75f), 0.75, 0, enemySprite, r, flip);
    }

    Player *SDLFactory::createPlayer() {
        SDL_Surface *frogSprite;
        if (playerSprite == NULL) {
            frogSprite = IMG_Load(s->getSettings()->spriteFrog.c_str());
            if (frogSprite != NULL) {
                playerSprite = r->createTexture(frogSprite);
            }
        }
        float wStart = calc_width(s->getSettings()->screenHeight, s->getSettings()->spriteFrogW,
                                  s->getSettings()->spriteFrogH); //Keeps image aspect ratio intact
        Player *p = new SDLPlayer(50.0, 8, (wStart * 0.75f), 0.75f, 1, playerSprite, r, this, this->s);
        return p;
    }

    Enemy *SDLFactory::createHealthPack(int lane) {
        bool flip = false;
        SDL_Surface *healthSprite;
        if (healthPackSprite == NULL) {
            healthSprite = IMG_Load(s->getSettings()->spriteHealth.c_str());
            if (healthSprite != NULL) {
                healthPackSprite = r->createTexture(healthSprite);
            }
        }
        float xStart, wStart, yStart = lane;
        wStart = calc_width(s->getSettings()->screenHeight, s->getSettings()->spriteHealthW,
                            s->getSettings()->spriteHealthH);
        if (lane > 3) {
            yStart++;
            xStart = 105.0f; //percentage
        }
        else {
            xStart = -15.0f;
        }
        return new SDLEnemy(xStart, yStart, (wStart * 0.75f), 0.75, 2, healthPackSprite, r, flip);
    }

    Enemy *SDLFactory::createAmmoPack(int lane) {
        bool flip = false;
        SDL_Surface *ammoSprite;
        if (ammoPackSprite == NULL) {
            ammoSprite = IMG_Load(s->getSettings()->spriteAmmo.c_str());
            if (ammoSprite != NULL) {
                ammoPackSprite = r->createTexture(ammoSprite);
            }
        }
        float xStart, wStart, yStart = lane;
        wStart = calc_width(s->getSettings()->screenHeight, s->getSettings()->spriteAmmoW,
                            s->getSettings()->spriteAmmoH);
        if (lane > 3) {
            yStart++;
            xStart = 105.0f; //percentage
        }
        else {
            xStart = -15.0f;
        }
        return new SDLEnemy(xStart, yStart, (wStart * 0.75f), 0.75, 3, ammoPackSprite, r, flip);
    }

    projectile *SDLFactory::createProjectile(float startX, int startY, float destX, float destY) {
        // movement of projectile is float in both X and Y dir, and does not snap to grid
        SDL_Surface *projectileSprite;
        if (projSprite == NULL) {
            projectileSprite = IMG_Load(s->getSettings()->spriteBullet.c_str());
            if (projectileSprite != NULL) {
                projSprite = r->createTexture(projectileSprite);
            }
        }
        startY = (100 / s->getSettings()->gridSize) * startY + 2;//convert lane to percentage
        startX += 4;
        return new SDLProjectile(startX, startY, 2, 2, 4, destX, destY, projSprite, r);
    }

    void SDLFactory::close() {
        if (r != NULL) {
            r->close();
            delete r;
        }
    }

    void SDLFactory::update() {
        if (r != NULL) {
            r->update();
        }
    }

    void SDLFactory::endUpdate() {
        if (r != NULL) {
            r->endUpdate();
        }
    }


    int SDLFactory::init() {
        if (r == NULL) {
            r = new Renderer(s);
        }
        r->createWindow();
        int i = r->loadMedia();
        if (i == 1) {
            r->loadBG();
            return 1;
        }
        return 0;
    }

    float SDLFactory::calc_width(int scrh, int w, int h) {
        //screenh/grid
        //origh/ans
        //return origW/ans
        return (((float) w / ((float) h / ((float) scrh / 9))) / (float) scrh) * 100;
    }

    FPSReg *SDLFactory::createFPSRegulator(int cap) {
        return new SDLFPSReg(cap);
    }

    void SDLFactory::renderText(float x, float y, float w, float h, string text) {
        r->renderText(x, y, w, h, text, {0, 0, 0});
    }

    void SDLFactory::playFX(int fx) {
        r->playFX(fx);
    }



}











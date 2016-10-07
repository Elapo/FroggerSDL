//
// Created by Frederik on 02/06/2016.
//

#include <sstream>
#include <map>
#include "settings.h"

namespace game_settings {
    settings::settings() {
        this->ts = new techSetting();
        this->ud = new userData();
        read();
    }

    void settings::save() {
        setFile.open("frogger.ini");
        if (setFile.is_open()) {
            setFile << "[Engine]\n" << "SCREEN_HEIGHT:" << ts->screenHeight << "\n"
            << "SCREEN_WIDTH:" << ts->screenWidth << "\n"
            << "GRID_SIZE:" << ts->gridSize << "\n"
            << "SPRITE_BG:" << ts->spriteBG << "\n"
            << "SPRITE_FROG:" << ts->spriteFrog << "\n"
            << "SPRITE_FROG_W:" << ts->spriteFrogW << "\n"
            << "SPRITE_FROG_H:" << ts->spriteFrogH << "\n"
            << "SPRITE_CAR_1:" << ts->spriteCar1 << "\n"
            << "SPRITE_CAR_W:" << ts->spriteCarW << "\n"
            << "SPRITE_CAR_H:" << ts->spriteCarH << "\n"
            << "SPRITE_HEALTH:" << ts->spriteHealth << "\n"
            << "SPRITE_HEALTH_W:" << ts->spriteHealthW << "\n"
            << "SPRITE_HEALTH_H:" << ts->spriteHealthH << "\n"
            << "SPRITE_AMMO:" << ts->spriteAmmo << "\n"
            << "SPRITE_AMMO_W:" << ts->spriteAmmoW << "\n"
            << "SPRITE_AMMO_H:" << ts->spriteAmmoH << "\n"
            << "SPRITE_BULLET:" << ts->spriteBullet << "\n"
            << "SPRITE_BULLET_W:" << ts->spriteBulletW << "\n"
            << "SPRITE_BULLET_H:" << ts->spriteBulletH << "\n"
            << "TTF_ROBOTO:" << ts->TTFRoboto << "\n"
            << "TEXT_SIZE:" << ts->textSize << "\n"
            << "BGM_MEGALOVANIA:" << ts->mainBGM << "\n";
            setFile << "[UserData]\n" << "HIGHSCORE:" << ud->highScore << "\n"
            << "HIGHSCORE_LEVEL:" << ud->highScore_level << "\n";
        }
        setFile.close();
    }

    techSetting *settings::getSettings() {
        return this->ts;
    }

    userData *settings::getUserData() {
        return this->ud;
    }

    void settings::read() {
        string line, setting, name;
        map<string, string> inputData;
        map<string, string>::iterator it;
        getFile.open("frogger.ini");
        if (getFile.is_open()) {
            while (getline(getFile, line)) {
                int pos = line.find(":");
                //printf("%d\n", pos);
                if (pos != -1) {
                    name = line.substr(0, pos);
                    setting = line.substr(pos + 1);
                    inputData.insert(make_pair(name, setting));
                }
            }
            getFile.close();
        }
        else {
            createNewINI();
            return;
        }
        //get all values from map to struct
        int converted;
        //auto will deduce type when it is assigned we do this because map.find() returns different types based on whether it can find the specified key or not.
        auto temp = inputData.find("SCREEN_HEIGHT"); //temp is either iterator to element or iterator itself when key is not found
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->screenHeight = converted;
        }
        else ts->screenHeight = 720;//standaard waarden

        temp = inputData.find("SCREEN_WIDTH");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->screenWidth = converted;
        }
        else ts->screenWidth = 960;

        temp = inputData.find("GRID_SIZE");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->gridSize = converted;
        }
        else ts->gridSize = 10;

        temp = inputData.find("SPRITE_BG");
        if (temp != inputData.end()) {
            ts->spriteBG = temp->second;
        }
        else ts->spriteBG = "Assets/backGround.png";

        temp = inputData.find("SPRITE_FROG");
        if (temp != inputData.end()) {
            ts->spriteFrog = temp->second;
        }
        else ts->spriteFrog = "Assets/frog.png";

        temp = inputData.find("SPRITE_FROG_W");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteFrogW = converted;
        }
        else ts->spriteFrogW = 816;

        temp = inputData.find("SPRITE_FROG_H");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteFrogH = converted;
        }
        else ts->spriteFrogH = 680;

        temp = inputData.find("SPRITE_CAR_1");
        if (temp != inputData.end()) {
            ts->spriteCar1 = temp->second;
        }
        else ts->spriteCar1 = "Assets/car.png";

        temp = inputData.find("SPRITE_CAR_W");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteCarW = converted;
        }
        else ts->spriteCarW = 2200;

        temp = inputData.find("SPRITE_CAR_H");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteCarH = converted;
        }
        else ts->spriteCarH = 1190;

        temp = inputData.find("SPRITE_HEALTH");
        if (temp != inputData.end()) {
            ts->spriteHealth = temp->second;
        }
        else ts->spriteHealth = "Assets/Health.png";

        temp = inputData.find("SPRITE_HEALTH_W");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteHealthW = converted;
        }
        else ts->spriteHealthW = 150;

        temp = inputData.find("SPRITE_HEALTH_H");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteHealthH = converted;
        }
        else ts->spriteHealthH = 150;

        temp = inputData.find("SPRITE_AMMO");
        if (temp != inputData.end()) {
            ts->spriteAmmo = temp->second;
        }
        else ts->spriteAmmo = "Assets/Ammo.png";

        temp = inputData.find("SPRITE_AMMO_W");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteAmmoW = converted;
        }
        else ts->spriteAmmoW = 825;

        temp = inputData.find("SPRITE_AMMO_H");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteAmmoH = converted;
        }
        else ts->spriteAmmoH = 825;

        temp = inputData.find("SPRITE_BULLET");
        if (temp != inputData.end()) {
            ts->spriteBullet = temp->second;
        }
        else ts->spriteBullet = "Assets/Bullet.png";

        temp = inputData.find("SPRITE_BULLET_W");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteBulletW = converted;
        }
        else ts->spriteBulletW = 50;

        temp = inputData.find("SPRITE_BULLET_H");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->spriteBulletH = converted;
        }
        else ts->spriteBulletH = 50;

        temp = inputData.find("TTF_ROBOTO");
        if (temp != inputData.end()) {
            ts->TTFRoboto = temp->second;
        }
        else ts->TTFRoboto = "Assets/Roboto-Bold.ttf";

        temp = inputData.find("TEXT_SIZE");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ts->textSize = converted;
        }
        else ts->textSize = 28;

        temp = inputData.find("BGM_MEGALOVANIA");
        if (temp != inputData.end()) {
            ts->mainBGM = temp->second;
        }
        else ts->mainBGM = "Assets/Megalovania.mp3";

        temp = inputData.find("HIGHSCORE");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ud->highScore = converted;
        }
        else ud->highScore = 0;

        temp = inputData.find("HIGHSCORE_LEVEL");
        if (temp != inputData.end()) {
            istringstream(temp->second) >> converted;
            ud->highScore_level = converted;
        }
        else ud->highScore_level = 1;
    }

    void settings::createNewINI() {
        this->ts->screenHeight = 720;
        this->ts->screenWidth = 960;
        this->ts->gridSize = 10;
        this->ts->spriteBG = "Assets/backGround.png";
        this->ts->spriteFrog = "Assets/frog.png";
        this->ts->spriteFrogW = 816;
        this->ts->spriteFrogH = 680;
        this->ts->spriteCar1 = "Assets/car.png";
        this->ts->spriteCarW = 2200;
        this->ts->spriteCarH = 1190;
        this->ts->spriteHealth = "Assets/Health.png";
        this->ts->spriteHealthW = 150;
        this->ts->spriteHealthH = 150;
        this->ts->spriteAmmo = "Assets/Ammo.png";
        this->ts->spriteAmmoW = 825;
        this->ts->spriteAmmoH = 825;
        this->ts->spriteBullet = "Assets/Bullet.png";
        this->ts->spriteBulletW = 50;
        this->ts->spriteBulletH = 50;
        this->ts->TTFRoboto = "Assets/Roboto-Bold.ttf";
        this->ts->textSize = 28;
        this->ts->mainBGM = "Assets/Megalovania.mp3";

        this->ud->highScore = 0;
        this->ud->highScore_level = 1;

        save();
    }
}












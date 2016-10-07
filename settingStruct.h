//
// Created by Frederik on 02/06/2016.
//

#ifndef FROGGERSDL_SETTINGSTRUCT_H
#define FROGGERSDL_SETTINGSTRUCT_H

#endif //FROGGERSDL_SETTINGSTRUCT_H

#include <string>
using namespace std;
namespace game_settings {
    struct techSetting {
        int screenHeight;/*<Window height in pixels*/
        int screenWidth;/*<Window width in pixels*/
        int gridSize;/*<How many "lanes"*/

        string spriteBG;/*<Background sprite location*/

        string spriteFrog;/*<Frog sprite*/
        int spriteFrogW;/*<Width of frog sprite*/
        int spriteFrogH;/*<Height of frog sprite*/

        string spriteCar1;/*<Car sprite*/
        int spriteCarW;/*<Width of car sprite*/
        int spriteCarH;/*<Height of frog sprite*/

        string spriteHealth;/*<Health sprite*/
        int spriteHealthW;/*<Width of Health sprite*/
        int spriteHealthH;/*<Height of Health sprite*/

        string spriteAmmo;/*<Ammo sprite*/
        int spriteAmmoW;/*<Width of Ammo sprite*/
        int spriteAmmoH;/*<Height of Ammo sprite*/

        string spriteBullet;/*<Bullet sprite*/
        int spriteBulletW;/*<Width of Bullet sprite*/
        int spriteBulletH;/*<Height of Bullet sprite*/

        string TTFRoboto;/*<Main font*/
        int textSize;/*<Font size*/

        string mainBGM;/*<Background music*/
    };

    struct userData {
        int highScore;/*<Highscore*/
        int highScore_level;/*<Highest level*/
    };
}
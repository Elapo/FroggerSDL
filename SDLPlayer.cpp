//
// Created by Frederik on 29/02/2016.
//

#include <iostream>
#include "SDLPlayer.h"
#include "keyNames.h"
namespace game_SDL {
    SDLPlayer::SDLPlayer(float x, float y, float h, float w, int type, SDL_Texture *t, Renderer *r, SDLFactory *f, settings* set)
            : Player(x, y, h, w, type, set) {
        texture = t;
        this->r = r;
        this->f = f;

        if(SDL_NumJoysticks() < 1){
            cout<< "No Joystick detected.\n";
        }
        else{
            gameController = SDL_GameControllerOpen(0);
            if(gameController == NULL){
                cout<<"Unable to open controller.\n";
            }
            haptic = SDL_HapticOpen(0);
            if(SDL_HapticRumbleInit(haptic)!=0){
                cout <<"Unable to init Haptic feedback.\n";
            }
        }
    }

    SDLPlayer::~SDLPlayer() {
        SDL_GameControllerClose(gameController);
        gameController = NULL;
        SDL_DestroyTexture(texture);
    }

    int SDLPlayer::getInput() {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return KEY_QUIT;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        return KEY_UP;
                    case SDLK_DOWN:
                        return KEY_DOWN;
                    case SDLK_LEFT:
                        return KEY_LEFT;
                    case SDLK_RIGHT:
                        return KEY_RIGHT;
                    case SDLK_SPACE:
                        return KEY_SPACE;
                    case SDLK_RETURN:
                        return KEY_ENTER;
                    default:
                        return KEY_NONE;
                }
            }
            if (e.type == SDL_CONTROLLERBUTTONDOWN) {
                switch (e.cbutton.button) {
                    case SDL_CONTROLLER_BUTTON_A:
                        return KEY_SPACE;
                    case SDL_CONTROLLER_BUTTON_START:
                        return KEY_ENTER;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        return KEY_UP;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        return KEY_DOWN;
                    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                        return KEY_LEFT;
                    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                        return KEY_RIGHT;
                    default:
                        cout << "Button: " << static_cast<int>(e.cbutton.button) << "\n";
                }
            }
            return 0;
        }
    }

    void SDLPlayer::Draw() {
        r->render(this->x, this->y, this->w, this->h, texture, false);
    }

    projectile *SDLPlayer::Shoot() {
        return f->createProjectile(this->x, (int) this->y, this->x, 0);
    }

    void SDLPlayer::rumble(int ms) {
        if(haptic != NULL) {
            SDL_HapticRumblePlay(haptic, 0.75, (Uint32) ms);
        }
    }
}






//
// Created by Frederik on 14/03/2016.
//

#include <iostream>
#include "Renderer.h"
#include "SDL2/SDL_Image.h"
using namespace std;
namespace game_SDL {
    Renderer::Renderer(settings *s) {
        set = s->getSettings();
    }

    void Renderer::render(float x, float y, float w, float h, SDL_Texture *t, bool fliph) {
        SDL_RendererFlip flipType = SDL_FLIP_NONE;
        if (fliph) {
            flipType = SDL_FLIP_HORIZONTAL;
        }
        translateGrid(&x, &y);
        translateGrid(&w, &h);
        SDL_Rect R = {(int) x, (int) y, (int) w, (int) h};
        if (t != NULL) {
            SDL_RenderCopyEx(renderer, t, NULL, &R, 0, 0, flipType);
        }
    }

    void Renderer::renderParticle(float x, float y, float w, float h, SDL_Texture *t) {
        translatePercent(&x, &y);
        translatePercent(&w, &h);
        SDL_Rect R = {(int) x, (int) y, (int) w, (int) h};
        if (t != NULL) {
            SDL_RenderCopy(renderer, t, NULL, &R);
        }
    }

    void Renderer::playFX(int fx){
        switch (fx){
            case 1:
                Mix_PlayChannel(2, jump, 0);
                break;
            case 2:
                Mix_PlayChannel(1, health, 0);
                break;
            case 3:
                Mix_PlayChannel(1, levelup, 0);
            default:
                //do nothing
                break;
        }
    }

    void Renderer::translatePercent(float *x, float *y) {
        *x = (set->screenWidth / 100) * (*x);
        *y = (set->screenHeight / 100) * (*y);

    }

    void Renderer::translateGrid(float *x, float *y) {
        *x = (set->screenWidth / 100) * (*x);
        *y = (set->screenHeight / set->gridSize) * (*y);
    }

    void Renderer::createWindow() {
        if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_GAMECONTROLLER|SDL_INIT_HAPTIC) < 0) {
            //ERROR
        }
        else {
            mainWindow = SDL_CreateWindow("Frogger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, set->screenWidth,
                                          set->screenHeight, SDL_WINDOW_SHOWN);
            if (mainWindow == NULL) {
                //ERROR
            }
            else {
                renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
                if (renderer != NULL) {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags)) {
                        cout << "Image initialisation failed\n";
                    }
                    else {
                        scrnSurface = SDL_GetWindowSurface(mainWindow);
                    }
                    if (TTF_Init() == -1) {
                        cout << "Font initialisation failed\n";
                    }
                    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                        cout << "Sound initialisation failed\n";
                    }
                    Mix_Volume(1, MIX_MAX_VOLUME/2);
                    Mix_Volume(2, MIX_MAX_VOLUME/8);
                }
            }
        }
    }

    void Renderer::loadBG() {
        SDL_Rect scrnRect = {0, 0, set->screenWidth,
                             (set->screenHeight / (set->gridSize) * (set->gridSize - 1)) - set->screenHeight / 50};
        SDL_RenderCopy(renderer, bgTexture, NULL, &scrnRect);
    }

    void Renderer::update() {
        if (Mix_PlayingMusic() == 0) { //if music isn't playing, play it
            Mix_PlayMusic(bgm, -1);
        }
        SDL_RenderClear(renderer);
        loadBG();
        if (textTexture != NULL) {
            SDL_RenderCopy(renderer, textTexture, NULL, textBox);
        }
    }

    void Renderer::endUpdate() {
        SDL_RenderPresent(renderer);
    }

    void Renderer::close() {

        SDL_FreeSurface(optiBg);
        optiBg = NULL;
        SDL_FreeSurface(scrnSurface);
        SDL_FreeSurface(backGround);
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(mainWindow);
        mainWindow = NULL;

        //cleanup audio
        Mix_FadeOutMusic(200);
        Mix_FreeMusic(bgm);
        Mix_FreeChunk(health);
        Mix_FreeChunk(jump);
        Mix_FreeChunk(levelup);
        Mix_CloseAudio();

        //cleanup ttf
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
        TTF_Quit();

        //quit SDL
        SDL_Quit();
    }

    int Renderer::loadMedia() {
        optiBg = NULL;

        try {
            backGround = IMG_Load(set->spriteBG.c_str());
            font = TTF_OpenFont(set->TTFRoboto.c_str(), set->textSize); //load font
            bgm = Mix_LoadMUS(set->mainBGM.c_str());//load BGM: MP3 WITHOUT TAG!! 44100Hz SR (higher will cause slowdown)
            jump = Mix_LoadWAV("Assets/jump.wav");
            health = Mix_LoadWAV("Assets/health.wav");
            levelup = Mix_LoadWAV("Assets/levelup.wav");
        }
        catch (exception e) {
            return 0;
        }
        if (backGround != NULL) {
            optiBg = SDL_ConvertSurface(backGround, scrnSurface->format, 0);
            bgTexture = SDL_CreateTextureFromSurface(renderer, optiBg);
            SDL_SetTextureColorMod(bgTexture, 255, 255, 255);
            if (optiBg != NULL && bgm != NULL && font != NULL && jump != NULL && health != NULL && levelup != NULL) {
                //SDL_FreeSurface(backGround);
                return 1;
            }
            return 0;
        }
        return 0;
    }

    SDL_Texture *Renderer::createTexture(SDL_Surface *s) {
        if (s != NULL) {
            SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
            if (t != NULL) {
                return t;
            }
            else {
                return NULL;
            }
        }
        return NULL;
    }

    void Renderer::renderText(float x, float y, float w, float h, string text, SDL_Color textColor) {
        SDL_DestroyTexture(textTexture);
        translateGrid(&x, &y);
        translateGrid(&w, &h);
        SDL_Surface *textSurface = TTF_RenderText_Shaded(font, text.c_str(), textColor, {255, 255, 255});
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textBox == NULL) {
            textBox = new SDL_Rect(); //allocate memory if not done already
        }
        textBox->x = (int) x;
        textBox->y = (int) y;
        textBox->w = textSurface->w;
        textBox->h = (int) h;
        //SDL_FreeSurface(textSurface);
    }
}












//
// Created by Frederik on 2/05/2016.
//

#include <SDL2/SDL_timer.h>
#include <cstdio>
#include "SDLFPSReg.h"
namespace game_SDL {
    SDLFPSReg::SDLFPSReg(int cap) : FPSReg(cap) {
        ticksPerFrame = 1000 / cap;
    }

    void SDLFPSReg::cap() {
        int frameticks = SDL_GetTicks() - startTicks;
        //printf("%d\r\n",frameticks);
        if ((frameticks) < ticksPerFrame) {
            SDL_Delay((uint32_t) (ticksPerFrame - frameticks));
        }
    }

    void SDLFPSReg::startCap() {
        startTicks = SDL_GetTicks();
    }
}






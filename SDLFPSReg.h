//
// Created by Frederik on 2/05/2016.
//

#ifndef FROGGERSDL_SDLFPSREG_H
#define FROGGERSDL_SDLFPSREG_H


#include "FPSReg.h"
using namespace game_Core;
namespace game_SDL {
    /*! SDL implementation of the framerate cap*/
    class SDLFPSReg : public FPSReg {
    public:
        /*!
         * Constructor
         * \param cap int, the frame rate cap
         */
        SDLFPSReg(int cap);
        /*!
         * Called every frame to delay next frame
         */
        void cap();
        /*!
         * Start the cap timer
         */
        void startCap();
    };
}


#endif //FROGGERSDL_SDLFPSREG_H

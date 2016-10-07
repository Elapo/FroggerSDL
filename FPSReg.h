#ifndef FROGGERSDL_FPSREG_H
#define FROGGERSDL_FPSREG_H

namespace game_Core {
    /*!
     * FPS Regulator class.
     */
    class FPSReg {
    public:
        /*!
         * Constructor
         * \param cap int, the frame rate cap
         */
        FPSReg(int cap);
        /*!
         * Called every frame to delay next frame
         */
        virtual void cap() = 0;
        /*!
         * Start the cap timer
         */
        virtual void startCap() = 0;

    protected:
        int ticksPerFrame, startTicks; /*!< calculated values for internal use*/
    };
}

#endif //FROGGERSDL_FPSREG_H

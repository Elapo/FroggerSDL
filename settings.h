//
// Created by Frederik on 02/06/2016.
//

#ifndef FROGGERSDL_SETTINGS_H
#define FROGGERSDL_SETTINGS_H

#include <string>
#include <fstream>
#include "settingStruct.h"

using namespace std;
namespace game_settings {
    /*!
     * Class that handles ini file
     */
    class settings {
    public:
        //! Constructor
        settings();
        //! Saves the file to disk
        void save();
        /*!
         * \return all technical settings (resolution, image locations, ...)
         */
        techSetting *getSettings();
        /*!
         * \return all user data (Highscore)
         */
        userData *getUserData();

    private:
        /*!
         * Read the file from disk
         */
        void read();
        /*!
         * Create a new ini file with standard values
         */
        void createNewINI();
        techSetting *ts;/*!<struct containing all technical settings*/
        userData *ud;/*!<struct containing Highscore*/
        ofstream setFile;/*!<file writer*/
        ifstream getFile;/*!<file reader*/
    };
}


#endif //FROGGERSDL_SETTINGS_H

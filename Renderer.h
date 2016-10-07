//
// Created by Frederik on 14/03/2016.
//

#ifndef FROGGERSDL_RENDERER_H
#define FROGGERSDL_RENDERER_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "settings.h"

using namespace std;
using namespace game_settings;
namespace game_SDL {
    /*!
     * Class that handles media
     */
    class Renderer {
    public:
        /*!
         * Constructor
         * \param s settings, contains all settings read from ini
         */
        Renderer(settings *s);
        /*!
         * Renders texture onto window
         * \param x float, X position of entity on grid
         * \param y float, Y position of entity on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param t SDL_Texture*, pointer to texture to render
         * \param fliph bool, whether or not to mirror the image
         */
        void render(float x, float y, float w, float h, SDL_Texture *t, bool fliph);
        /*!
         * Create SDL window
         */
        void createWindow();
        /*!
         * Load the background
         */
        void loadBG();
        /*!
         * Clear screen, redraw text and background
         */
        void update();
        /*!
         * Present screen
         */
        void endUpdate();
        /*!
         * Remove all assets from memory and quit SDL
         */
        void close();
        /*!
         * Load all media from disk
         */
        int loadMedia();
        /*!
         * Translate grid values to pixels
         * \param x float, the x or width value to convert
         * \param y float, the y or height value to convert
         */
        void translateGrid(float *x, float *y);
        /*!
         * Translate grid values to pixels, with Y being a percentage instead of a "lane"
         * \param x float, the x or width value to convert
         * \param y float, the y or height value to convert
         */
        void translatePercent(float *x, float *y);
        /*!
         * Creates a texure from surface
         * \param surface to convert
         * \return texture from surface
         */
        SDL_Texture *createTexture(SDL_Surface *s);
        /*!
         * Update the text texture
         * \param x float, X position of text on grid
         * \param y float, Y position of text on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         * \param text string, contains new text
         * \param textColor, contains text color values in RGB
         */
        void renderText(float x, float y, float w, float h, string text, SDL_Color textColor);
        /*!
         * Render an object that does not use "lanes", such as a particle
         * \param x float, X position of particle on grid
         * \param y float, Y position of particle on grid
         * \param w float, width in grid values
         * \param h float, height in grid values
         */
        void renderParticle(float x, float y, float w, float h, SDL_Texture *t);
        /*!
         * plays sound effect
         * \param fx int, identifier of the sound effect
         */
        void playFX(int fx);

    private:
        SDL_Window *mainWindow = NULL;
        SDL_Surface *scrnSurface = NULL;
        SDL_Surface *backGround = NULL;
        SDL_Surface *optiBg = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Texture *bgTexture = NULL;
        TTF_Font *font = NULL;
        Mix_Music *bgm = NULL;
        Mix_Chunk* jump = NULL;
        Mix_Chunk* health = NULL;
        Mix_Chunk* levelup = NULL;
        SDL_Texture *textTexture = NULL;
        SDL_Rect *textBox = NULL;
        techSetting *set;
    };
}
#endif //FROGGERSDL_RENDERER_H

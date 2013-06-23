/* MineFree: sdlhandler.cpp
 * Copyright (C) 2012-2013 Sebastian Szymak
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License, version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "sdlhandler.h"

#include <sstream>

#include "log.h"
#include "error.h"
#include "config.h"
#include "build.h"

SdlHandler::SdlHandler() : screen(0), width(0), height(0), bpp(0)
{
        Config &config = Config::getInstance();

        width  = config.getScreenWidth();
        height = config.getScreenHeight();
        bpp    = config.getScreenBpp();
}

SdlHandler::~SdlHandler()
{
        if (0 != screen) {
                LOGINF("Closing SDL surface.");
                SDL_FreeSurface(screen);
        }

        SDL_Quit();
        LOGINF("Quit!");
}

int SdlHandler::init(void) {
        int error = 0;

        if (screen) {
                LOGWRN("SDL initialization already done!");
                error = MF_ERROR_SDL_INIT;
        }

        if (!error) {
                if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                        LOGERR("Couldn't initialize SDL: " << SDL_GetError());
                        error = MF_ERROR_SDL_INIT;
                }
        }

        if (!error) {
                LOGINF("SDL initialization done.");

                screen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL);

                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

                if (0 == screen) {
                        LOGERR("Couldn't set " << getVideoMode() <<
                                        " video mode: " << SDL_GetError());
                        error = MF_ERROR_SDL_INIT;
                }
        }

        if (!error) {
                LOGINF("Video mode: " << getVideoMode());
                SDL_WM_SetCaption(MINEFREE, MINEFREE);
        }
        
        return error;
}

std::string SdlHandler::getVideoMode(void) const {
        std::stringstream stream;

        stream << width << "x" << height << "x" << bpp;
        return stream.str();
}

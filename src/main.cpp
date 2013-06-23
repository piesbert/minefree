/* MineFree: main.cpp
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
#include "ogrehandler.h"
#include "gameloop.h"
#include "build.h"
#include "scene.h"

#include "ogrewrapper.h"

int main(int argc, char **argv) {
#if 0
        int error = 0;

        SdlHandler  sdlHandler;
        OgreHandler ogreHandler;
        GameLoop    gameLoop(ogreHandler);
        Scene       scene(ogreHandler);

        error = sdlHandler.init();

        if (!error) {
                error = ogreHandler.init();
        }

        if (!error) {
                scene.init();
                gameLoop.run();
        }

        return error;
#endif
        OgreWrapper ogre;
        ogre.init();

        while (!(ogre.getRenderWindow()->isClosed())) {
                Ogre::WindowEventUtilities::messagePump();
        }

        return 0;
}
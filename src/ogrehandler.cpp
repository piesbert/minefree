/* MineFree: ogrehandler.cpp
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

#include "ogrehandler.h"

#include <SDL/SDL.h>

#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"

#include "error.h"
#include "build.h"
#include "log.h"
#include "config.h"

OgreHandler::OgreHandler()
: root(0), log(0), renderWindow(0)
{
}

OgreHandler::~OgreHandler()
{
                delete root;
                delete log;
}

int OgreHandler::init() {
        error = 0;

        /* check if any component is initialized already
         */
        if (log || root || renderWindow) {
                LOGERR("OGRE initialization already done.");
                error = MF_ERROR_OGRE_INIT;
        }
        
        if (!error) {
                initLog();
                initRoot();
        }

        if (!error) {
                initWindow();
        }

        return error;       
}

void OgreHandler::renderFrame() const {
        root->renderOneFrame();
        SDL_GL_SwapBuffers();
}

void OgreHandler::initLog() {
        log = new Ogre::LogManager();
        log->createLog(OGRE_LOG_PATH, true, false, false);

        if (log) {
                LOGINF("Ogre log file created: " << OGRE_LOG_PATH);
        }
        else {
                LOGERR("Couldn't create Ogre log object.");
                error = MF_ERROR_OGRE_INIT;
        }
}

void OgreHandler::initRoot() {
        root = new Ogre::Root(PLUGINS_CFG_PATH, OGRE_CFG_PATH, "");

        if (root) {
                LOGINF("Ogre::Root object initialized.");
        }
        else {
                LOGERR("Couldn't create Ogre root object.");
                error = MF_ERROR_OGRE_INIT;
        }
}

void OgreHandler::initWindow() {
        Ogre::NameValuePairList misc;
        Config &config = Config::getInstance();

        int width  = config.getScreenWidth();
        int height = config.getScreenHeight();


        root->restoreConfig();
        root->initialise(false);

        misc["currentGLContext"] = Ogre::String("True");

        renderWindow = root->createRenderWindow(
                        "MainRenderWindow",
                        width, height, false, &misc);

        if (renderWindow) {
                renderWindow->setVisible(true);
                LOGINF("Render window: " << width << "x" << height << ".");
        }
        else {
                LOGERR("Couldn't create Ogre render window");
                error = MF_ERROR_OGRE_INIT;
        }
}

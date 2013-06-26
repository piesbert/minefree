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

#include "build.h"
#include "ogrewrapper.h"
#include "inputmanager.h"
#include "fppcamera.h"
#include "motionstate.h"


void quitCallback(bool asdf) {
        exit(0);
}

int main(int argc, char **argv) {
        OgreWrapper ogre;
        FppCamera camera;
        MotionState &motion = MotionState::getInstance();

        ogre.init();
        camera.init(ogre);

        ActionManager::getInstance().addListener(ActionManager::QUIT, quitCallback, "QUIT");
        
        ActionManager::getInstance().addListener(ActionManager::MOVE_FORWARD, MotionState::setForward, "FORWARD");
        ActionManager::getInstance().addListener(ActionManager::MOVE_BACKWARD, MotionState::setBackward, "BACKWARD");
        ActionManager::getInstance().addListener(ActionManager::MOVE_LEFT, MotionState::setStrafeLeft, "STRAFELEFT");
        ActionManager::getInstance().addListener(ActionManager::MOVE_RIGHT, MotionState::setStrafeRight, "STRAFERIGHT");


        while (!(ogre.getRenderWindow()->isClosed())) {
                ogre.update();
                ogre.captureEvents();
                camera.transform();
        }

        return 0;
}

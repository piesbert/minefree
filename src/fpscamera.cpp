/* MineFree: fpscamera.cpp
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

#include "fpscamera.h"

#include "error.h"
#include "log.h"

#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgreEntity.h"

FpsCamera::FpsCamera(Ogre::RenderWindow &rw, Ogre::SceneManager &sm)
: camera(0), renderWindow(rw), sceneManager(sm)
{
}

FpsCamera::~FpsCamera()
{
}

int FpsCamera::init() {
        int error = 0;

        if (camera) {
                LOGERR("FPS Camera initialized already!");
                error = MF_ERROR_OGRE_FPS_CAMERA_INIT;
        }
        else {
                camera = sceneManager.createCamera("FPS");
                if (camera) {
                        cameraNode = sceneManager.getRootSceneNode()->createChildSceneNode("FPSNode");

                        cameraNode->setPosition(0, 10, 200);
                        cameraNode->attachObject(camera);
                        camera->lookAt(Ogre::Vector3(0,0,0));
                        camera->setNearClipDistance(5);

                        LOGINF("FPS Camera created");
                }
                else {
                        LOGERR("Couldn't create FPS Camera.");
                        error = MF_ERROR_OGRE_FPS_CAMERA_INIT;
                }
        }

        if (!error) {
                viewport = renderWindow.addViewport(camera);
                viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

                camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

                LOGINF("Viewport init done.");
        }
        
        return error;
}

/* MineFree: scene.cpp
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

#include "scene.h"

#include "ogrehandler.h"
#include "error.h"
#include "log.h"
#include "fpscamera.h"

Scene::Scene(const OgreHandler &h)
: handler(h), fpsCamera(0), scene(0)
{
}

Scene::~Scene()
{
        delete fpsCamera;
}

int Scene::init() {
        int error = 0;

        if (scene) {
                LOGERR("Scene manager initialized already.");
                error = MF_ERROR_OGRE_SCENE_INIT;
        }

        if (!error) {
                scene = handler.getRoot().createSceneManager(Ogre::ST_GENERIC, "SceneManager");
                if (scene) {
                        rootNode = scene->getRootSceneNode();

                        if (0 == rootNode) {
                                LOGERR("Couldn't create root scene node.");
                                error = MF_ERROR_OGRE_SCENE_INIT;
                        }
                }
                else {
                        LOGERR("Couldn't initialize scene Manager.");
                        error = MF_ERROR_OGRE_SCENE_INIT;
                }
        }

        if (!error) {
                fpsCamera = new FpsCamera(handler.getWindow(), *scene);
                fpsCamera->init();
        }

        return error;
}

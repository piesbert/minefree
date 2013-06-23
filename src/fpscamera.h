/* MineFree: fpscamera.h
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

#if !defined(LOCK_MINEFREE_FPSCAMERA_H)
#define LOCK_MINEFREE_FPSCAMERA_H

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderSystem.h"
#include "OGRE/OgreRenderWindow.h"

class FpsCamera {
        public:
                FpsCamera(Ogre::RenderWindow &, Ogre::SceneManager &);
                virtual ~FpsCamera();

                int init();

        private:
                Ogre::Camera *camera;
                Ogre::SceneNode *cameraNode;
                Ogre::Viewport *viewport;

                Ogre::RenderWindow &renderWindow;
                Ogre::SceneManager &sceneManager;

                FpsCamera(FpsCamera const&); // do not implement
                FpsCamera operator=(FpsCamera const&); // do not implement
}; // class FpsCamera

#endif //LOCK_MINEFREE_FPSCAMERA_H

/* MineFree: scene.h
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

#if !defined(LOCK_MINEFREE_SCENE_H)
#define LOCK_MINEFREE_SCENE_H

#include "OGRE/OgreRoot.h"

class OgreHandler;
class FpsCamera;

class Scene {
        public:
                Scene(const OgreHandler &);
                virtual ~Scene();

                int init();

        private:
                const OgreHandler &handler;

                FpsCamera *fpsCamera;

                Ogre::SceneManager *scene;
                Ogre::SceneNode    *rootNode;

                Scene(Scene const&); // do not implement
                Scene operator=(Scene const&); // do not implement
}; // class Scene

#endif //LOCK_MINEFREE_SCENE_H

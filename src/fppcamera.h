/* MineFree: fppcamera.h
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

#if !defined(LOCK_MINEFREE_FPPCAMERA_H)
#define LOCK_MINEFREE_FPPCAMERA_H

#include "ogrewrapper.h"

class FppCamera {
        public:
                FppCamera();
                virtual ~FppCamera();

                void init(const OgreWrapper &);

                void forward(bool);
                void backward(bool);

        private:
                Ogre::Camera    *m_camera;
                Ogre::SceneNode *m_cameraNode;
                Ogre::Viewport  *m_viewport;

                void createViewport(const OgreWrapper &);
                void test(const OgreWrapper &);

                FppCamera(FppCamera const&); // do not implement
                FppCamera operator=(FppCamera const&); // do not implement
}; // class FppCamera

#endif //LOCK_MINEFREE_FPPCAMERA_H

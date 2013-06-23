/* MineFree: ogrehandler.h
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

#if !defined(LOCK_MINEFREE_OGREHANDLER_H)
#define LOCK_MINEFREE_OGREHANDLER_H

#include <OGRE/OgreRoot.h>

class OgreHandler {
        public:
                OgreHandler();
                virtual ~OgreHandler();

                int init();

                Ogre::Root &getRoot() const { return *root; };
                Ogre::RenderWindow &getWindow() const { return *renderWindow; };

                void renderFrame() const;

        private:
                Ogre::Root *root;
                Ogre::LogManager *log;
                Ogre::RenderWindow *renderWindow;

                int error;

                void initLog();
                void initRoot();
                void initWindow();

                OgreHandler(OgreHandler const&); // do not implement
                OgreHandler operator=(OgreHandler const&); // do not implement
}; // class OgreHandler

#endif //LOCK_MINEFREE_OGREHANDLER_H

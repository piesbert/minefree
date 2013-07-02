/* MineFree: ogrewrapper.h
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

#if !defined(LOCK_MINEFREE_OGREWRAPPER_H)
#define LOCK_MINEFREE_OGREWRAPPER_H

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include <exception>

#include "inputmanager.h"

class OgreWrapper {
        public:
                OgreWrapper();
                virtual ~OgreWrapper();

                void init();

                void captureEvents() const;
                void update() const;

                Ogre::Root         *getRoot() const;
                Ogre::RenderWindow *getRenderWindow() const;
                Ogre::SceneManager *getSceneManager() const;
                Ogre::SceneNode    *getRootSceneNode() const;

        private:
                Ogre::String m_configFile;
                Ogre::String m_pluginsFile;
                Ogre::String m_logFile;

                Ogre::Root         *m_root;
                Ogre::RenderSystem *m_renderSystem;
                Ogre::RenderWindow *m_renderWindow;
                Ogre::LogManager   *m_logManager;
                Ogre::SceneManager *m_sceneManager;
                Ogre::SceneNode    *m_rootSceneNode;

                InputManager       *m_inputManager;

                void initLogManager();
                void createRootObject();
                void loadPlugins();
                void selectRenderSystem();
                void initRootObject();
                void createWindow();
                void prepareScene();

                OgreWrapper(OgreWrapper const&); // do not implement
                OgreWrapper operator=(OgreWrapper const&); // do not implement
}; // class OgreWrapper

#endif //LOCK_MINEFREE_OGREWRAPPER_H

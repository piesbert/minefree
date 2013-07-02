/* MineFree: ogrewrapper.cpp
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

#include "ogrewrapper.h"

#include "log.h"
#include "build.h"
#include "config.h"

OgreWrapper::OgreWrapper() :
m_root(0),
m_renderSystem(0),
m_renderWindow(0), 
m_logManager(0),
m_sceneManager(0),
m_rootSceneNode(0),
m_inputManager(0) {
}

OgreWrapper::~OgreWrapper() {
        delete m_root;
}

void OgreWrapper::init() {
        initLogManager();
        createRootObject();

        if (m_root) {
                loadPlugins();
                selectRenderSystem();
                
                if (m_renderSystem) {
                        initRootObject();
                        createWindow();
                }
        }

        if (m_renderWindow) {
                prepareScene();

                m_inputManager = new InputManager();
                m_inputManager->init(m_root, m_renderWindow);
       }
}

void OgreWrapper::captureEvents() const {
        if (m_inputManager) {
                m_inputManager->capture();
        }
}

void OgreWrapper::update() const {
        m_renderWindow->update(false);
        m_renderWindow->swapBuffers(true);
        m_root->renderOneFrame();

        Ogre::WindowEventUtilities::messagePump();
}

Ogre::Root *OgreWrapper::getRoot() const {
        return m_root;
}

Ogre::RenderWindow *OgreWrapper::getRenderWindow() const {
        return m_renderWindow;
}

Ogre::SceneManager *OgreWrapper::getSceneManager() const {
        return m_sceneManager;
}

Ogre::SceneNode *OgreWrapper::getRootSceneNode() const {
        return m_rootSceneNode;
}

void OgreWrapper::initLogManager() {
        m_logManager = new Ogre::LogManager();
        m_logManager->createLog(OGRE_LOG_PATH, true, false, false);
}


void OgreWrapper::createRootObject() {
        m_configFile  = OGRE_CFG_PATH;
        m_pluginsFile = PLUGINS_CFG_PATH;
        m_logFile     = OGRE_LOG_PATH;

        if (!m_root) {
                m_root = new Ogre::Root(m_configFile, m_pluginsFile, m_logFile);


        }
}

void OgreWrapper::loadPlugins() {
        std::vector<Ogre::String>           plugins;
        std::vector<Ogre::String>::iterator i;
        
        bool isDebug = OGRE_DEBUG_MODE;

        plugins.push_back(std::string(OGRE_PLUGINS_PATH) + "RenderSystem_GL");
        plugins.push_back(std::string(OGRE_PLUGINS_PATH) + "Plugin_ParticleFX");
        plugins.push_back(std::string(OGRE_PLUGINS_PATH) + "Plugin_OctreeSceneManager");
        
        for (i = plugins.begin(); i < plugins.end(); i++) {
                Ogre::String &plugin = (*i);
                LOGINF(plugin);

                if (isDebug) {
                        plugin.append("_d");
                }

                m_root->loadPlugin(plugin);
        }
}

void OgreWrapper::selectRenderSystem() {
        const Ogre::RenderSystemList &renderList = m_root->getAvailableRenderers();

        if (renderList.size()) {
                m_renderSystem = renderList[0];
                m_root->setRenderSystem(m_renderSystem);
        }
}

void OgreWrapper::initRootObject() {
        /* Do not create window automatically.
         * This will be done in createWindow.
         */
        m_root->restoreConfig();
        m_root->initialise(false);
}

void OgreWrapper::createWindow() {
        Config &config = Config::getInstance();

        unsigned int width  = config.getScreenWidth();
        unsigned int height = config.getScreenHeight();
        
        bool fullscreen = config.getScreenFullscreen();

        Ogre::NameValuePairList params;

        params["FSAA"]  = config.getScreenParamFSAA();
        params["vsync"] = config.getScreenParamVSync();

        m_renderWindow = m_root->createRenderWindow(
                config.getScreenWindowTitle(),
                width,
                height,
                fullscreen,
                &params);

        m_renderWindow->setActive(true);
        m_renderWindow->setAutoUpdated(false);


        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(QUAKECONSOLE_MATERIALS_PATH, "FileSystem");
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreWrapper::prepareScene() {
        m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
        m_rootSceneNode = m_sceneManager->getRootSceneNode();
}

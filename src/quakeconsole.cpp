/* MineFree: quakeconsole.cpp
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

#include "quakeconsole.h"
#include "build.h"
#include "log.h"

QuakeConsole::QuakeConsole() :
m_root(0),
m_sceneManager(0),
m_overlay(0),
m_textbox(0),
m_panel(0),
m_visible(false),
m_height(0.0) {
}

QuakeConsole::~QuakeConsole() {
}

void QuakeConsole::init(Ogre::Root *root) {
        m_root = root;
        m_root->addFrameListener(this);

        m_sceneManager = m_root->getSceneManagerIterator().getNext();

        m_overlay = Ogre::OverlayManager::getSingleton().getByName("QuakeConsole");
        m_textbox = Ogre::OverlayManager::getSingleton().getOverlayElement("QuakeConsole/Text");
        m_panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().getOverlayElement("QuakeConsole/Background"));
        m_overlay->show();
       
        Ogre::LogManager::getSingleton().getDefaultLog()->addListener(this);
}

void QuakeConsole::onKeyPressed(const OIS::KeyEvent &e) {
        if (!m_visible) {
                return;
        }
}

void QuakeConsole::setVisible(bool visible) {
        m_visible = visible;
}

bool QuakeConsole::getVisible() const {
        return m_visible;
}

bool QuakeConsole::frameStarted(const Ogre::FrameEvent &e) {
        if (m_visible && (m_height < 1)) {
                m_height += e.timeSinceLastFrame * 4;
                m_textbox->show();

                if (m_height >= 1) {
                        m_height = 1;
                }
        }
        else if (!m_visible && (m_height > 0)) {
                m_height -= e.timeSinceLastFrame * 4;
                if (m_height <= 0) {
                        m_height = 0;
                        m_textbox->hide();
                }
        }

        m_textbox->setPosition(0, (m_height -1) * 0.5);
        m_panel->setPosition(0, (m_height -1) * 0.5);

        return true;
}

bool QuakeConsole::frameEnded(const Ogre::FrameEvent &e) {
        return true;
}

void QuakeConsole::messageLogged(const Ogre::String &msg, Ogre::LogMessageLevel logLevel, bool debug, const Ogre::String &logName, bool &value) {
}

void QuakeConsole::messageLogged(const Ogre::String &msg, Ogre::LogMessageLevel logLevel, bool debug, const Ogre::String &logName) {
}

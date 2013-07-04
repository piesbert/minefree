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

const Ogre::String QuakeConsole::c_validChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890+!\"#%&/()=?[]\\*-_.:,; ";
const unsigned int QuakeConsole::c_maxLines = 15;

QuakeConsole::QuakeConsole() :
m_root(0),
m_sceneManager(0),
m_overlay(0),
m_textbox(0),
m_panel(0) {
        m_visible   = false;
        m_update    = false;
        m_height    = 0.0;
        m_lastLine  = 0;
        m_startLine = 0;
        m_newPrefix = true;
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
        if (m_visible) {
                /* Return pressed.
                 */
                if ((OIS::KC_RETURN == e.key) && (m_prompt.length() > 0)) {
                        handleLine(m_prompt);
                        m_prompt = "";
                        m_newPrefix = true;
                        m_commandManager.resetIndex();
                }

                /* Backspace pressed.
                 */
                else if (OIS::KC_BACK == e.key) {
                        if (m_prompt.length() > 0) {
                                m_prompt.erase(m_prompt.end() - 1);
                                m_newPrefix = true;
                        }
                        
                        if (0 == m_prompt.length()) {
                                m_commandManager.resetIndex();
                        }
                }

                /* PgUp pressed.
                 */
                else if ((OIS::KC_PGUP == e.key) && (m_startLine > c_maxLines)) {
                        m_startLine--;
                }

                /* PgDown pressed.
                 */
                else if ((OIS::KC_PGDOWN == e.key) && (m_startLine < m_lastLine)) {
                        m_startLine++;
                }

                /* TAB pressed
                 */
                else if (OIS::KC_TAB == e.key) {
                        if (m_newPrefix) {
                                m_prefix = m_prompt;
                                m_newPrefix = false;
                        }

                        m_prompt = m_commandManager.getNext(m_prefix) + " ";
                }

                /* Normal keys.
                 */
                else {
                        size_t length = c_validChars.length();

                        for (size_t i = 0; i < length; i++) {
                                if (c_validChars[i] == (int)(e.text)) {
                                        m_prompt += e.text;
                                        break;
                                }
                        }

                        m_newPrefix = true;
                }

                m_update = true;
        }
}

void QuakeConsole::handleLine(const Ogre::String &line) {
        m_lines.push_back(line);

        if (m_startLine == m_lastLine) {
                m_startLine++;
        }

        m_lastLine++;
}

void QuakeConsole::setVisible(bool visible) {
        m_visible = visible;

        if (m_visible) {
                m_update = true;
        }
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

        if (m_update) {
                Ogre::String text;
                std::list<Ogre::String>::iterator line;
                unsigned int counter;

                if (m_startLine > m_lines.size()) {
                        m_startLine = m_lines.size();
                }

                line = m_lines.begin();
                
                for (int i = 0; i < ((int)(m_startLine) - int(c_maxLines)); i++) {
                        line++;
                }

                counter = 0;
                while ((line != m_lines.end()) && (counter++ < c_maxLines)) {
                        text += (*line) + "\n";
                        line++;
                }

                text += "$ " + m_prompt + "_";
                m_textbox->setCaption(text);

                m_update = false;
        }

        return true;
}

bool QuakeConsole::frameEnded(const Ogre::FrameEvent &e) {
        return true;
}

void QuakeConsole::messageLogged(const Ogre::String &msg, Ogre::LogMessageLevel logLevel, bool debug, const Ogre::String &logName, bool &value) {
}

void QuakeConsole::messageLogged(const Ogre::String &msg, Ogre::LogMessageLevel logLevel, bool debug, const Ogre::String &logName) {
}

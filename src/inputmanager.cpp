/* MineFree: inputmanager.cpp
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

#include "inputmanager.h"
#include "motionstate.h"

InputManager::InputManager() :
m_mouse(0),
m_keyboard(0),
m_input(0),
m_actionManager(ActionManager::getInstance()) {
}

InputManager::~InputManager() {
        if (m_input) {
                if (m_mouse) {
                        m_input->destroyInputObject(m_mouse);
                        m_mouse = 0;
                }

                if (m_keyboard) {
                        m_input->destroyInputObject(m_keyboard);
                        m_keyboard = 0;
                }

                m_input->destroyInputSystem(m_input);
                m_input = 0;
        }
}

void InputManager::init(Ogre::RenderWindow *window) {
        if (!m_input) {
                OIS::ParamList paramList;
                std::ostringstream windowHandlerStream;
                size_t windowHandler;

                windowHandler = 0;
                window->getCustomAttribute("WINDOW", &windowHandler);

                windowHandlerStream << (unsigned int) windowHandler;
                paramList.insert(std::make_pair(std::string("WINDOW"), windowHandlerStream.str()));

                m_input = OIS::InputManager::createInputSystem(paramList);

                if (m_input->getNumberOfDevices(OIS::OISKeyboard) > 0) {
                        m_keyboard = static_cast<OIS::Keyboard*>(m_input->createInputObject(OIS::OISKeyboard, true));
                        m_keyboard->setEventCallback(this);
                }

                if (m_input->getNumberOfDevices(OIS::OISMouse) > 0) {
                        unsigned int width;
                        unsigned int height;
                        unsigned int depth;

                        int left;
                        int top;
                        
                        m_mouse = static_cast<OIS::Mouse*>(m_input->createInputObject(OIS::OISMouse, true));
                        m_mouse->setEventCallback(this);

                        window->getMetrics(width, height, depth, left, top);
                        setWindowExtents(width, height);
                }
        }
}

void InputManager::capture() const {
        if (m_keyboard) {
                m_keyboard->capture();
        }
        if (m_mouse) {
                m_mouse->capture();
        }
}

bool InputManager::keyPressed(const OIS::KeyEvent &e) {
        m_actionManager.broadcast(e, true);
        return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent &e) {
        m_actionManager.broadcast(e, false);
        return true;
}

bool InputManager::mouseMoved(const OIS::MouseEvent &e) {
        if (m_mouse) {
                MotionState::getInstance().setPitch(e.state.Y.rel);
                MotionState::getInstance().setYaw(e.state.X.rel);
        }

        return true;
}

bool InputManager::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
        return true;
}

bool InputManager::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
        return true;
}

void InputManager::setWindowExtents(int width, int height) {
        const OIS::MouseState &state = m_mouse->getMouseState();

        state.width = width;
        state.height = height;
}

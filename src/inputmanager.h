/* MineFree: inputmanager.h
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

#if !defined(LOCK_MINEFREE_INPUTMANAGER_H)
#define LOCK_MINEFREE_INPUTMANAGER_H

#include "actionmanager.h"

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISInputManager.h>

#include <OGRE/OgreRenderWindow.h>

class InputManager : public OIS::KeyListener, public OIS::MouseListener {
        public:
                InputManager();
                virtual ~InputManager();

                void init(Ogre::RenderWindow *window);
                void capture() const;

        private:
                OIS::Mouse        *m_mouse;
                OIS::Keyboard     *m_keyboard;
                OIS::InputManager *m_input;

                ActionManager     &m_actionManager;

                InputManager(InputManager const&); // do not implement
                InputManager operator=(InputManager const&); // do not implement

                bool keyPressed(const OIS::KeyEvent &e);
                bool keyReleased(const OIS::KeyEvent &e);

                bool mouseMoved(const OIS::MouseEvent &e);
                bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
                bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

                void setWindowExtents(int width, int height);
}; // class InputManager

#endif //LOCK_MINEFREE_INPUTMANAGER_H

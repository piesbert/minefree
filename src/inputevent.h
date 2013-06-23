/* MineFree: inputevent.h
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

#if !defined(LOCK_MINEFREE_INPUTEVENT_H)
#define LOCK_MINEFREE_INPUTEVENT_H

#include <OIS/OISMouse.h>
#include <OIS/OISKeyboard.h>

class InputEvent {
        public:
                enum Type {NONE = 0, KEYBOARD, MOUSE, QUIT, MAX};

                InputEvent();

                virtual ~InputEvent();

                bool setType(InputEvent::Type);
                bool setKey(OIS::KeyCode);
                bool setKey(OIS::MouseButtonID);

                bool match(const OIS::KeyEvent &) const;
                bool match(const OIS::MouseEvent &, OIS::MouseButtonID) const;

        private:
                InputEvent::Type m_type;
                unsigned int     m_key;

                bool set(InputEvent::Type, unsigned int);

                InputEvent(InputEvent const&); // do not implement
                InputEvent operator=(InputEvent const&); // do not implement
}; // class InputEvent

#endif //LOCK_MINEFREE_INPUTEVENT_H

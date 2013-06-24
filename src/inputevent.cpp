/* MineFree: inputevent.cpp
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

#include "inputevent.h"
#include "log.h"

InputEvent::InputEvent()
: m_type(InputEvent::NONE), m_key(0) {
}

InputEvent::~InputEvent() {
}

bool InputEvent::setType(InputEvent::Type type) {
        return set(type, m_key);
}

bool InputEvent::setKey(OIS::KeyCode key) {
        return set(m_type, (unsigned int)key);
}

bool InputEvent::setKey(OIS::MouseButtonID id) {
        return set(m_type, (unsigned int)id);
}

bool InputEvent::match(const OIS::KeyEvent &event) const {
        bool retval = false;

        LOGINF(m_type << ".." << m_key << ".." << event.key);

        if ((KEYBOARD == m_type) && (event.key == m_key)) {
                retval = true;
        }

        return retval;
}

bool InputEvent::match(const OIS::MouseEvent &event, OIS::MouseButtonID id) const {
        bool retval = false;

        if ((MOUSE == m_type) && (id == m_key)) {
                retval = true;
        }

        return retval;
}

bool InputEvent::set(InputEvent::Type type, unsigned int key) {
        bool retval = false;

        if (type < InputEvent::MAX) {
                m_type = type;
                m_key = key;

                retval = true;
        }

        return retval;
}

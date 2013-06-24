/* MineFree: actionmanager.cpp
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

#include "actionmanager.h"

ActionManager::ActionManager() {
        prepareDefaults();
}

ActionManager::~ActionManager() {
}

ActionManager& ActionManager::getInstance() {
        static ActionManager instance;
        return instance;
}

void ActionManager::prepareDefaults() {
        /* Quit event.
         */
        events[QUIT].setType(InputEvent::KEYBOARD);
        events[QUIT].setKey(OIS::KC_ESCAPE);

        /* Menu events.
         */
        events[MENU_UP].setType(InputEvent::KEYBOARD);
        events[MENU_UP].setKey(OIS::KC_UP);
        events[MENU_DOWN].setType(InputEvent::KEYBOARD);
        events[MENU_DOWN].setKey(OIS::KC_DOWN);
        events[MENU_SELECT].setType(InputEvent::KEYBOARD);
        events[MENU_SELECT].setKey(OIS::KC_RETURN);
}

bool ActionManager::addListener(ActionManager::ActionID id, const Callback callback, const std::string &name) {
        return events[id].add(callback, name);
}

void ActionManager::removeListener(ActionManager::ActionID id, const std::string &name) {
        events[id].remove(name);
}

void ActionManager::broadcast(const OIS::KeyEvent &event, bool value) {
        for (int i = 0; i < (int)ActionManager::MAX; i++) {
                if (events[i].match(event)) {
                        events[i].run(value);
                }
        }
}

void ActionManager::broadcast(const OIS::MouseEvent &event, OIS::MouseButtonID button, bool value) {
        for (int i = 0; i < (int)ActionManager::MAX; i++) {
                if (events[i].match(event, button)) {
                        events[i].run(value);
                }
        }
}

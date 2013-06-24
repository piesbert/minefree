/* MineFree: actionmanager.h
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

#if !defined(LOCK_MINEFREE_ACTIONMANAGER_H)
#define LOCK_MINEFREE_ACTIONMANAGER_H

#include <string>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include "event.h"

class ActionManager {
        public:
                enum ActionID {
                        QUIT = 0,
                        MENU_UP,
                        MENU_DOWN,
                        MENU_SELECT,
                        MOVE_UP,
                        MOVE_DOWN,
                        MOVE_LEFT,
                        MOVE_RIGHT,
                        MAX
                };

                static ActionManager& getInstance();

                bool addListener(ActionManager::ActionID, const Callback, const std::string &);
                void removeListener(ActionManager::ActionID, const std::string &);

                void broadcast(const OIS::KeyEvent &, bool);
                void broadcast(const OIS::MouseEvent &, OIS::MouseButtonID, bool);

                virtual ~ActionManager();

        private:
                Event events[MAX];

                void prepareDefaults();

                ActionManager();
                ActionManager(ActionManager const&); // do not implement
                ActionManager operator=(ActionManager const&); // do not implement
}; // class ActionManager

#endif //LOCK_MINEFREE_ACTIONMANAGER_H

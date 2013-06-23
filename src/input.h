/* MineFree: input.h
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

#if !defined(LOCK_MINEFREE_INPUT_H)
#define LOCK_MINEFREE_INPUT_H

#include <SDL/SDL.h>

typedef void (*Action)(bool);

struct EventType {
        enum {
                KEYBOARD = 0,
                MOUSEBUTTON,
                QUIT,
                MAX
        };
}; // struct EventType

struct ActionCode {
        enum {
                QUIT = 0,
                ESCAPE,
                UP,
                DOWN,
                LEFT,
                RIGHT,
                JUMP,
                USE,
                MAX
        };
}; // struct ActionCode

struct Event {
        int type;
        int key;
}; // struct Event

class Input {
        public:
                static Input& instance();

                void registerAction(int, Action);
                void handleEvents();

        private:
                Event events[ActionCode::MAX];
                Action actions[ActionCode::MAX];

                Action handleEvent(const SDL_Event &);
                void defaultEvents();

                Input();
                virtual ~Input();
                Input(Input const&); // do not implement
                Input operator=(Input const&); // do not implement
}; // class Input

#endif //LOCK_MINEFREE_INPUT_H

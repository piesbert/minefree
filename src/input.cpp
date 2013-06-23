/* MineFree: input.cpp
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

#include "input.h"

#include "log.h"

Input::Input()
{
        defaultEvents();
}

Input::~Input()
{
}

Input& Input::instance() {
        static Input input;
        return input;
}

void Input::registerAction(int code, Action action) {
        if (ActionCode::MAX > code) {
                actions[code] = action;
        }
        else {
                LOGERR("Invalid action code: " << code);
        }
}

void Input::handleEvents() {
        SDL_Event ev;
        Action action;
        bool value;

        while (SDL_PollEvent(&ev)) {
                action = 0;
                value  = true;

                /* handle quit event - user closes window with [x]
                 */
                if (ev.type == SDL_QUIT) {
                        action = actions[ActionCode::QUIT];
                }

                /* handle key down events
                 */
                else if (ev.type == SDL_KEYDOWN ||
                         ev.type == SDL_MOUSEBUTTONDOWN) {
                        action = handleEvent(ev);
                }

                /* handle key up events
                 */
                else if (ev.type == SDL_KEYUP ||
                         ev.type == SDL_MOUSEBUTTONUP) {
                        action = handleEvent(ev);
                        value  = false;
                }

                if (0 != action) {
                        (*action)(value);
                }
        }
}

Action Input::handleEvent(const SDL_Event &ev) {
        Action action = 0;

        for (int i = 0; i < ActionCode::MAX; i++) {
                if (EventType::KEYBOARD == events[i].type &&
                    ev.key.keysym.sym == events[i].key) {
                        action = actions[i];
                        break;
                }
                else if (EventType::MOUSEBUTTON == events[i].type &&
                         ev.button.button == events[i].key) {
                        action = actions[i];
                        break;
                }
        }

        return action;
}

void Input::defaultEvents() {
        events[ActionCode::QUIT].type = EventType::QUIT;
        events[ActionCode::QUIT].key = 0;

        events[ActionCode::ESCAPE].type = EventType::KEYBOARD;
        events[ActionCode::ESCAPE].key = SDLK_ESCAPE;

        events[ActionCode::UP].type = EventType::KEYBOARD;
        events[ActionCode::UP].key = SDLK_w;

        events[ActionCode::DOWN].type = EventType::KEYBOARD;
        events[ActionCode::DOWN].key = SDLK_s;

        events[ActionCode::LEFT].type = EventType::KEYBOARD;
        events[ActionCode::LEFT].key = SDLK_a;

        events[ActionCode::RIGHT].type = EventType::KEYBOARD;
        events[ActionCode::RIGHT].key = SDLK_d;

        events[ActionCode::JUMP].type = EventType::KEYBOARD;
        events[ActionCode::JUMP].key = SDLK_SPACE;

        events[ActionCode::USE].type = EventType::MOUSEBUTTON;
        events[ActionCode::USE].key = SDL_BUTTON_LEFT;
}

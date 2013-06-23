/* MineFree: gameloop.cpp
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

#include "gameloop.h"

#include "log.h"
#include "input.h"
#include "ogrehandler.h"

bool GameLoop::running = true;

GameLoop::GameLoop(const OgreHandler &h)
: handler(h)
{
        Input::instance().registerAction((int)ActionCode::QUIT, &GameLoop::quit);
        Input::instance().registerAction((int)ActionCode::ESCAPE, &GameLoop::quit);
}

GameLoop::~GameLoop()
{
}

void GameLoop::run() {
        while (GameLoop::running) {
                Input::instance().handleEvents();
                handler.renderFrame();
        }
}

void GameLoop::quit(bool quit) {
        if (quit) {
                GameLoop::running = false;
        }
}

/* MineFree: gameloop.h
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

#if !defined(LOCK_MINEFREE_GAMELOOP_H)
#define LOCK_MINEFREE_GAMELOOP_H

class OgreHandler;

class GameLoop {
        public:
                GameLoop(const OgreHandler &);
                virtual ~GameLoop();

                void run();
                static void quit(bool);

        private:
                const OgreHandler &handler;
                static bool running;

                GameLoop(GameLoop const&); // do not implement
                GameLoop operator=(GameLoop const&); // do not implement
}; // class GameLoop

#endif //LOCK_MINEFREE_GAMELOOP_H

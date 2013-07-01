/* MineFree: quakeconsole.cpp
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

#include "quakeconsole.h"

QuakeConsole::QuakeConsole() {
}

QuakeConsole::~QuakeConsole() {
}

QuakeConsole& QuakeConsole::getInstance() {
        static QuakeConsole instance;
        return instance;
}

bool QuakeConsole::frameStarted(const Ogre::FrameEvent &e) {
        return true;
}

bool QuakeConsole::frameEnded(const Ogre::FrameEvent &e) {
        return true;
}

void QuakeConsole::messageLogged(const Ogre::String &msg, Ogre::LogMessageLevel logLevel, bool debug, const Ogre::String &logName, bool &value) {
}


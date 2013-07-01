/* MineFree: quakeconsole.h
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

#if !defined(LOCK_MINEFREE_QUAKECONSOLE_H)
#define LOCK_MINEFREE_QUAKECONSOLE_H

#include <OGRE/Ogre.h>
#include <OGRE/OgreFrameListener.h>

#include <OIS/OIS.h>

#include <string>
#include <list>
#include <vector>

class QuakeConsole : public Ogre::FrameListener, Ogre::LogListener {
        public:
                static QuakeConsole& getInstance();
                virtual ~QuakeConsole();

                void init(Ogre::Root *);

                void setVisible(bool);
                void getVisible();

                virtual bool frameStarted(const Ogre::FrameEvent &);
                virtual bool frameEnded(const Ogre::FrameEvent &);

                void messageLogged(const Ogre::String &, Ogre::LogMessageLevel, bool, const Ogre::String &, bool&);

        private:
                QuakeConsole();
                QuakeConsole(QuakeConsole const&); // do not implement
                QuakeConsole operator=(QuakeConsole const&); // do not implement
}; // class QuakeConsole

#endif //LOCK_MINEFREE_QUAKECONSOLE_H

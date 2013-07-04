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

#include "commandmanager.h"

#include <OGRE/Ogre.h>
#include <OGRE/OgreFrameListener.h>

#include <OIS/OIS.h>

#include <string>
#include <list>

class QuakeConsole : public Ogre::FrameListener, Ogre::LogListener {
        public:
                QuakeConsole();
                virtual ~QuakeConsole();

                void init(Ogre::Root *);

                void setVisible(bool);
                bool getVisible() const;

                void onKeyPressed(const OIS::KeyEvent &);
                void handleLine(const Ogre::String &);

                virtual bool frameStarted(const Ogre::FrameEvent &);
                virtual bool frameEnded(const Ogre::FrameEvent &);

                /* OGRE ver. 1.8.0
                 */
                void messageLogged(const Ogre::String &, Ogre::LogMessageLevel, bool, const Ogre::String &, bool&);

                /* OGRE ver. 1.7.4
                 */
                void messageLogged(const Ogre::String &, Ogre::LogMessageLevel, bool, const Ogre::String &);

        private:
                Ogre::Root             *m_root;
                Ogre::SceneManager     *m_sceneManager;
                Ogre::Overlay          *m_overlay;
                Ogre::OverlayElement   *m_textbox;
                Ogre::OverlayContainer *m_panel;

                bool  m_visible;
                bool  m_update;
                float m_height;
                bool  m_newPrefix;

                Ogre::String            m_prompt;
                Ogre::String            m_prefix;
                std::list<Ogre::String> m_lines;
                unsigned int            m_lastLine;
                unsigned int            m_startLine;

                static const Ogre::String c_validChars;
                static const unsigned int c_maxLines;

                CommandManager m_commandManager;

                QuakeConsole(QuakeConsole const&); // do not implement
                QuakeConsole operator=(QuakeConsole const&); // do not implement
}; // class QuakeConsole

#endif //LOCK_MINEFREE_QUAKECONSOLE_H

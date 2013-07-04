/* MineFree: commandmanager.h
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

#if !defined(LOCK_MINEFREE_COMMANDMANAGER_H)
#define LOCK_MINEFREE_COMMANDMANAGER_H

#include "command.h"

#include <vector>
#include <string>

class CommandManager {
        public:
                CommandManager();
                virtual ~CommandManager();

                void resetIndex();
                const std::string &getNext(const std::string &);

        private:
                std::vector<Command*> m_vector;

                std::string m_prefix;
                int         m_index;

                int findFirst(const std::string &) const;
                bool isValid(const std::string &, const std::string &) const;

                CommandManager(CommandManager const&); // do not implement
                CommandManager operator=(CommandManager const&); // do not implement
}; // class CommandManager

#endif //LOCK_MINEFREE_COMMANDMANAGER_H

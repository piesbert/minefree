/* MineFree: commandmanager.cpp
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

#include "commandmanager.h"
#include "log.h"

CommandManager::CommandManager() {
        m_prefix = "";

        m_vector.push_back(new Command("m_pitch"));
        m_vector.push_back(new Command("m_yaw"));
        m_vector.push_back(new Command("quit"));
        m_vector.push_back(new Command("sensitivity"));
}

CommandManager::~CommandManager() {
        for (int i = 0; i < (int)(m_vector.size()); i++) {
                delete m_vector[i];
        }
}

void CommandManager::resetIndex() {
        m_index = 0;
}

const std::string& CommandManager::getNext(const std::string &prefix) {
        if (0 != prefix.compare(m_prefix)) {
                m_prefix = prefix;
                m_index  = findFirst(m_prefix);
        }
        else {
                if (m_index >= (int)(m_vector.size())) {
                        m_index = findFirst(m_prefix);
                }
                else if (!isValid(m_vector[m_index]->getName(), m_prefix)) {
                        m_index = findFirst(m_prefix);
                }
        }

        return m_vector[m_index++]->getName();
}


int CommandManager::findFirst(const std::string &prefix) const {
        int retval = 0;

        for (unsigned int i = 0; i < m_vector.size(); i++) {
                if (isValid(m_vector[i]->getName(), prefix)) {
                        retval = i;
                        break;
                }
        }

        return retval;
}

bool CommandManager::isValid(const std::string &text, const std::string &prefix) const {
        bool retval = false;

        if (0 == prefix.length()) {
                retval = true;
        }
        else if (0 == text.compare(0, prefix.length(), prefix)) {
                retval = true;
        }

        return retval;
}


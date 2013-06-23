/* MineFree: callbackqueue.cpp
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

#include "callbackqueue.h"

#include "log.h"

CallbackQueue::CallbackQueue() {
}

CallbackQueue::~CallbackQueue() {
}

bool CallbackQueue::add(const Callback callback, const std::string &name) {
        std::pair<std::map<std::string, Callback>::iterator, bool> ret;

        ret = queue.insert(std::pair<std::string, Callback>(name, callback));
        return (ret.second);
}

void CallbackQueue::remove(const std::string &name) {
        queue.erase(name);
}

void CallbackQueue::run(bool value) {
        std::map<std::string, Callback>::iterator i;

        for (i = queue.begin(); i != queue.end(); i++) {
                (*(i->second))(value);
        }
}

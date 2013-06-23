/* MineFree: callbackqueue.h
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

#if !defined(LOCK_MINEFREE_CALLBACKQUEUE_H)
#define LOCK_MINEFREE_CALLBACKQUEUE_H

#include <string>
#include <map>

typedef void (*Callback)(bool);

class CallbackQueue {
        public:
                CallbackQueue();
                virtual ~CallbackQueue();

                bool add(const Callback, const std::string &);
                void remove(const std::string &);

                void run(bool) ;

        private:
                std::map<std::string, Callback> queue;

                CallbackQueue(CallbackQueue const&); // do not implement
                CallbackQueue operator=(CallbackQueue const&); // do not implement
}; // class CallbackQueue

#endif // LOCK_MINEFREE_CALLBACKQUEUE_H

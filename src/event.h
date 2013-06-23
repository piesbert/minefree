/* MineFree: event.h
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

#if !defined(LOCK_MINEFREE_EVENT_H)
#define LOCK_MINEFREE_EVENT_H

#include "inputevent.h"
#include "callbackqueue.h"

class Event : public InputEvent, public CallbackQueue {
        public:
                Event();
                virtual ~Event();

        private:
                Event(Event const&); // do not implement
                Event operator=(Event const&); // do not implement
}; // class Event

#endif //LOCK_MINEFREE_EVENT_H

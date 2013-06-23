/* MineFree: log.h
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

#if !defined(LOCK_MINEFREE_LOG_H)
#define LOCK_MINEFREE_LOG_H

#include <iostream>
#include <libgen.h>

#if defined(FULL_PREFIX)
#define PREFIX basename((char *)__FILE__) << "(" << __LINE__ << ") in " << __FUNCTION__ << "(): "
#else
#define PREFIX ""
#endif

#define LOGERR(MSG) std::cerr << "E " << PREFIX << MSG << std::endl
#define LOGWRN(MSG) std::cerr << "W " << PREFIX << MSG << std::endl
#define LOGINF(MSG) std::cout << "I " << PREFIX << MSG << std::endl

#endif //LOCK_MINEFREE_LOG_H

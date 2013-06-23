/* MineFree: config.h
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

#if !defined(LOCK_MINEFREE_CONFIG_H)
#define LOCK_MINEFREE_CONFIG_H

#include <string>

class Config {
        public:
                static Config& getInstance();
                virtual ~Config();

                int getScreenWidth() const;
                int getScreenHeight() const;
                int getScreenBpp() const;
                
                bool getScreenFullscreen() const;

                std::string getScreenWindowTitle() const;
                std::string getScreenParamFSAA() const;
                std::string getScreenParamVSync() const;

        private:
                Config();
                Config(Config const&); // do not implement
                Config operator=(Config const&); // do not implement
}; // class Config

#endif //LOCK_MINEFREE_CONFIG_H

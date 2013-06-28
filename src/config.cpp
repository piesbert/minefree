/* MineFree: config.cpp
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

#include "config.h"

Config::Config() {
}

Config::~Config() {
}

Config& Config::getInstance() {
        static Config config;
        return config;
}

int Config::getScreenWidth(void) const {
        return 800;
}

int Config::getScreenHeight(void) const {
        return 600;
}

int Config::getScreenBpp(void) const {
        return 32;
}

bool Config::getScreenFullscreen() const {
        return false;
}

std::string Config::getScreenWindowTitle() const {
        return "MineFree";
}

std::string Config::getScreenParamFSAA() const {
        return "4";
}

std::string Config::getScreenParamVSync() const {
        return "true";
}

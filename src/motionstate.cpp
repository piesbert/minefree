/* MineFree: motionstate.cpp
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

#include "motionstate.h"

bool MotionState::m_forward = false;
bool MotionState::m_backward = false;
bool MotionState::m_strafeLeft = false;
bool MotionState::m_strafeRight = false;

MotionState::MotionState() {
}

MotionState::~MotionState() {
}

MotionState& MotionState::getInstance() {
        static MotionState instance;
        return instance;
}

void MotionState::setForward(bool state) {
        if ((m_forward = state) && m_backward) {
                m_backward = false;
        }
}

void MotionState::setBackward(bool state) {
        if ((m_backward = state) && m_forward) {
                m_forward = false;
        }
}


void MotionState::setStrafeLeft(bool state) {
        if ((m_strafeLeft = state) && m_strafeRight) {
                m_strafeRight = false;
        }
}

void MotionState::setStrafeRight(bool state) {
        if ((m_strafeRight = state) && m_strafeLeft) {
                m_strafeLeft = false;
        }
}


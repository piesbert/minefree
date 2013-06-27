/* MineFree: motionstate.h
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

#if !defined(LOCK_MINEFREE_MOTIONSTATE_H)
#define LOCK_MINEFREE_MOTIONSTATE_H

class MotionState {
        public:
                static MotionState &getInstance();

                virtual ~MotionState();

                static void setForward(bool);
                static void setBackward(bool);
                static void setStrafeLeft(bool);
                static void setStrafeRight(bool);

                static bool goForward() { return m_forward; };
                static bool goBackward() { return m_backward; };
                static bool goStrafeLeft() { return m_strafeLeft; };
                static bool goStrafeRight() { return m_strafeRight; };


                static void setPitch(float pitch);
                static void setYaw(float yaw);

                static float getPitch();
                static float getYaw();

        private:
                static bool m_forward;
                static bool m_backward;
                static bool m_strafeLeft;
                static bool m_strafeRight;

                static float m_pitch;
                static float m_yaw;

                MotionState();
                MotionState(MotionState const&); // do not implement
                MotionState operator=(MotionState const&); // do not implement
}; // class MotionState

#endif //LOCK_MINEFREE_MOTIONSTATE_H

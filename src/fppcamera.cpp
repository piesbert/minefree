/* MineFree: fppcamera.cpp
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

#include "fppcamera.h"
#include "motionstate.h"

#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreEntity.h>

FppCamera::FppCamera() :
m_camera(0),
m_cameraNode(0),
m_yawNode(0),
m_pitchNode(0),
m_rollNode(0),
m_viewport(0),
m_transVector(Ogre::Vector3::ZERO),
m_moveStep(1.0f) {
}

FppCamera::~FppCamera() {
}

void FppCamera::init(const OgreWrapper &ogre) {
        m_camera = ogre.getSceneManager()->createCamera("FPPCamera");
        
        m_cameraNode = ogre.getRootSceneNode()->createChildSceneNode("FPPCameraNode");
        m_yawNode    = m_cameraNode->createChildSceneNode();
        m_pitchNode  = m_yawNode->createChildSceneNode();
        m_rollNode   = m_pitchNode->createChildSceneNode();

        m_rollNode->attachObject(m_camera);

        createViewport(ogre);

        if (m_viewport) {
                float ratio = float(m_viewport->getActualWidth()) /
                              float(m_viewport->getActualHeight());

                m_camera->setAspectRatio(ratio);
                m_camera->setNearClipDistance(1.5f);
                m_camera->setFarClipDistance(3000.0f);

                test(ogre);
        }
}

void FppCamera::transform() {
        MotionState &state = MotionState::getInstance();
        Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

        if (state.goForward()) {
                transVector.z -= m_moveStep;
        }

        if (state.goBackward()) {
                transVector.z += m_moveStep;
        }

        if (state.goStrafeLeft()) {
                transVector.x -= m_moveStep;
        }

        if (state.goStrafeRight()) {
                transVector.x += m_moveStep;
        }

        m_cameraNode->translate(transVector, Ogre::Node::TS_LOCAL);
}

void FppCamera::createViewport(const OgreWrapper &ogre) {
        float width  = 1.0f;
        float height = 1.0f;

        float left   = (1.0f - width) * 0.5f;
        float top    = (1.0f - height) * 0.5f;

        unsigned short zOrder = 100;

        m_viewport = ogre.getRenderWindow()->addViewport(
                m_camera, zOrder, left, top, width, height);

        m_viewport->setAutoUpdated(true);
        m_viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
}

void FppCamera::test(const OgreWrapper &ogre)
{
        Ogre::ManualObject* lManualObject = NULL;
        {
                Ogre::String lManualObjectName = "CubeWithAxes";
                lManualObject = ogre.getSceneManager()->createManualObject(lManualObjectName);

                bool lDoIWantToUpdateItLater = false;
                lManualObject->setDynamic(lDoIWantToUpdateItLater);

                float lSize = 0.7f;
                lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
                {
                        float cp = 1.0f * lSize ;
                        float cm = -1.0f * lSize;

                        lManualObject->position(cm, cp, cm);// a vertex
                        lManualObject->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
                        lManualObject->position(cp, cp, cm);// a vertex
                        lManualObject->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
                        lManualObject->position(cp, cm, cm);// a vertex
                        lManualObject->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
                        lManualObject->position(cm, cm, cm);// a vertex
                        lManualObject->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));

                        lManualObject->position(cm, cp, cp);// a vertex
                        lManualObject->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
                        lManualObject->position(cp, cp, cp);// a vertex
                        lManualObject->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
                        lManualObject->position(cp, cm, cp);// a vertex
                        lManualObject->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
                        lManualObject->position(cm, cm, cp);// a vertex
                        lManualObject->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));

                        lManualObject->triangle(0,1,2);
                        lManualObject->triangle(2,3,0);
                        lManualObject->triangle(4,6,5);
                        lManualObject->triangle(6,4,7);
                        lManualObject->triangle(0,4,5);
                        lManualObject->triangle(5,1,0);
                        lManualObject->triangle(2,6,7);
                        lManualObject->triangle(7,3,2);
                        lManualObject->triangle(0,7,4);
                        lManualObject->triangle(7,0,3);
                        lManualObject->triangle(1,5,6);
                        lManualObject->triangle(6,2,1);                 
                }
                lManualObject->end();
#if 0
                lManualObject->begin("BaseWhiteNoLighting",Ogre::RenderOperation::OT_LINE_LIST);
                {
                        float lAxeSize = 2.0f * lSize;
                        lManualObject->position(0.0f, 0.0f, 0.0f);
                        lManualObject->colour(Ogre::ColourValue::Red);
                        lManualObject->position(lAxeSize, 0.0f, 0.0f);
                        lManualObject->colour(Ogre::ColourValue::Red);
                        lManualObject->position(0.0f, 0.0f, 0.0f);
                        lManualObject->colour(Ogre::ColourValue::Green);
                        lManualObject->position(0.0, lAxeSize, 0.0);
                        lManualObject->colour(Ogre::ColourValue::Green);
                        lManualObject->position(0.0f, 0.0f, 0.0f);
                        lManualObject->colour(Ogre::ColourValue::Blue);
                        lManualObject->position(0.0, 0.0, lAxeSize);
                        lManualObject->colour(Ogre::ColourValue::Blue);

                        lManualObject->index(0);
                        lManualObject->index(1);
                        lManualObject->index(2);
                        lManualObject->index(3);
                        lManualObject->index(4);
                        lManualObject->index(5);
                }
                lManualObject->end();
#endif
        }
        Ogre::String lNameOfTheMesh = "MeshCubeAndAxe";
        Ogre::String lResourceGroup = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
        lManualObject->convertToMesh(lNameOfTheMesh);

        int lNumberOfEntities = 5;
        for(int iter = 0; iter < lNumberOfEntities; ++iter)
        {
                Ogre::Entity* lEntity = ogre.getSceneManager()->createEntity(lNameOfTheMesh);
                Ogre::SceneNode* lNode = ogre.getRootSceneNode()->createChildSceneNode();
                lNode->attachObject(lEntity);
                float lPositionOffset = float(1+ iter * 2) - (float(lNumberOfEntities));
                lNode->translate(lPositionOffset, lPositionOffset, -10.0f);
        }
}



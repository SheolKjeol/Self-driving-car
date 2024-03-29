/**
 * Based on: lanefollower - Sample application for following lane markings.
 * Copyright (C) 2012 - 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "LaneFollower.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::data::image;
        using namespace automotive;
        using namespace automotive::miniature;

        LaneFollower::LaneFollower(const int32_t &argc, char **argv) : TimeTriggeredConferenceClientModule(argc, argv, "lanefollower"),
            m_hasAttachedToSharedImageMemory(false),
            m_sharedImageMemory(),
            m_image(NULL),
            m_debug(false),
            m_font(),
            m_previousTime(),
            m_eSum(0),
            m_eOld(0),
            midLane(0),
            firstMeasure(true),
            
            no_lines(false),
            overtake(false),

            m_vehicleControl() {}

        LaneFollower::~LaneFollower() {}

        void LaneFollower::setUp() {
        }

        void LaneFollower::tearDown() {
            // This method will be call automatically _after_ return from body().
            if (m_image != NULL) {
                cvReleaseImage(&m_image);
            }
        }

        bool LaneFollower::readSharedImage(Container &c) {
            bool retVal = false;

            if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                SharedImage si = c.getData<SharedImage> ();

                // Check if we have already attached to the shared memory.
                if (!m_hasAttachedToSharedImageMemory) {
                    m_sharedImageMemory
                            = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(
                                    si.getName());
                }

                // Check if we could successfully attach to the shared memory.
                if (m_sharedImageMemory->isValid()) {
                    // Lock the memory region to gain exclusive access using a scoped lock.
                    Lock l(m_sharedImageMemory);
                    const uint32_t numberOfChannels = 3;
                    // For example, simply show the image.
                    if (m_image == NULL) {
                        m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
                    }

                    // Copying the image data is very expensive...
                    if (m_image != NULL) {
                        memcpy(m_image->imageData,
                               m_sharedImageMemory->getSharedMemory(),
                               si.getWidth() * si.getHeight() * numberOfChannels);
                    }

                    // Mirror the image.
                    cvFlip(m_image, 0, -1);

                    retVal = true;
                }
            }
            return retVal;
        }

        double LaneFollower::findDeviation() {
            double e = 0;
            int prev_left_x = -1;
            int prev_right_x = -1;
            no_lines = false;

            const int32_t CONTROL_SCANLINE = 462; // calibrated length to right: 280px
            const int32_t distance = 280;

            TimeStamp beforeImageProcessing;
            for(int32_t y = m_image->height - 8; y > m_image->height * .6; y -= 10) {
                // Search from middle to the left:
                CvScalar pixelLeft;
                CvPoint left;
                left.y = y;
                left.x = prev_left_x;
                for(int x = m_image->width/2; x > 0; x--) {
                    pixelLeft = cvGet2D(m_image, y, x);
                    if (pixelLeft.val[0] >= 200) {
                        left.x = x;
                        prev_left_x = x;
                        break;
                    }
                }

                // Search from middle to the right:
                CvScalar pixelRight;
                CvPoint right;
                right.y = y;
                right.x = prev_right_x;
                for(int x = m_image->width/2; x < m_image->width; x++) {
                    pixelRight = cvGet2D(m_image, y, x);
                    if (pixelRight.val[0] >= 200) {
                        right.x = x;
                        prev_right_x = x;
                        break;
                    }
                }

                if (y == CONTROL_SCANLINE) {
                    // Calculate the deviation error.
                    if (right.x > 0) {
                        cerr << "RIGHT" << endl;
                        e = ((right.x - m_image->width/2.0) - distance)/distance;

                    }
                    else if (left.x > 0) {
                        cerr << "LEFT" << endl;
                        e = (distance - (m_image->width/2.0 - left.x))/distance;
                    }
                    else {
                        // If no measurements are available, reset PID controller.
                        e = 0;
                        no_lines = true;
                        cerr << "NONE" << endl;
                    }
            
                }
            }
            cerr << "DEVIATION FOUND = " << e << endl;
            return e;
        }

        void LaneFollower::processImage() {
            double e = findDeviation();
            cerr << "DEVIATION RECEIVED = " << e << endl;

            //TimeStamp afterImageProcessing;
            //cerr << "Processing time: " << (afterImageProcessing.toMicroseconds() - beforeImageProcessing.toMicroseconds())/1000.0 << "ms." << endl;
            TimeStamp currentTime;

            m_previousTime = currentTime;
            if (!no_lines) {
                const double y = e;
                double desiredSteering = 0;
                double speed = 1;
                if (fabs(e) > 1e-2) {
                    desiredSteering = y;
                    speed = 0.5; //slow down when in a curve
                    if (desiredSteering > 25.0) {
                            desiredSteering = 25.0;
                    }
                    if (desiredSteering < -25.0) {
                            desiredSteering = -25.0;
                    }
                }
                // Go forward.
                m_vehicleControl.setSpeed(speed);
                m_vehicleControl.setSteeringWheelAngle(desiredSteering);
                cerr << "PID: " << "e = " << e << ", eSum = " << m_eSum << ", desiredSteering = " << desiredSteering << ", y = " << y << ", speed = " << speed << endl;
            } else {
                m_vehicleControl.setSpeed(0.5); //super slow down when there are no lines
            }
        }

        

        // This method will do the main data processing job.
        // Therefore, it tries to open the real camera first. If that fails, the virtual camera images from camgen are used.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode LaneFollower::body() {

            const int32_t ULTRASONIC_FRONT_CENTER = 3;
            const int32_t ULTRASONIC_FRONT_RIGHT = 4;
            const int32_t INFRARED_FRONT_RIGHT = 0;
            const int32_t INFRARED_REAR_RIGHT = 2;

            const double OVERTAKING_DISTANCE = 6;
            const double HEADING_PARALLEL = 0.01;

            const double SPEED_FAST = 1;
            const double SPEED_SLOW = 0.5;

            // Overall state machines for moving and measuring.
            enum StateMachineMoving { FORWARD, TO_LEFT_LANE_LEFT_TURN, TO_LEFT_LANE_RIGHT_TURN, CONTINUE_ON_LEFT_LANE, TO_RIGHT_LANE_RIGHT_TURN, TO_RIGHT_LANE_LEFT_TURN };
            enum StateMachineMeasuring { DISABLE, FIND_OBJECT_INIT, FIND_OBJECT, FIND_OBJECT_PLAUSIBLE, HAVE_BOTH_IR, HAVE_BOTH_IR_SAME_DISTANCE, END_OF_OBJECT };

            StateMachineMoving stageMoving = FORWARD;
            StateMachineMeasuring stageMeasuring = FIND_OBJECT_INIT;

            // State counter for dynamically moving back to right lane.
            int32_t stageToRightLaneRightTurn = 0;
            int32_t stageToRightLaneLeftTurn = 0;

            // Distance variables to ensure we are overtaking only stationary or slowly driving obstacles.
            double distanceToObstacle = 0;
            double distanceToObstacleOld = 0;

            // Overall state machine handler.
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                bool has_next_frame = false;
                cerr << "STATE = " << stageMoving << endl;

                // Get the most recent available container for a SharedImage.
                Container c = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
                if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                    // Example for processing the received container.
                    has_next_frame = readSharedImage(c);
                }

                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(VehicleData::ID());
                VehicleData vd = containerVehicleData.getData<VehicleData> ();

                // 2. Get most recent sensor board data:
                Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();


                // Moving state machine.
                if (stageMoving == FORWARD && true == has_next_frame) {
                    // Go forward.
                    // vc.setSpeed(SPEED_FAST);
                    // vc.setSteeringWheelAngle(0);
                    processImage();

                    stageToRightLaneLeftTurn = 0;
                    stageToRightLaneRightTurn = 0;
                }
                else if (stageMoving == TO_LEFT_LANE_LEFT_TURN) {
                    // Move to the left lane: Turn left part until both IRs see something.
                    m_vehicleControl.setSpeed(SPEED_SLOW);
                    m_vehicleControl.setSteeringWheelAngle(-10);

                    // State machine measuring: Both IRs need to see something before leaving this moving state.
                    stageMeasuring = HAVE_BOTH_IR;

                    stageToRightLaneRightTurn++;
                }
                else if (stageMoving == TO_LEFT_LANE_RIGHT_TURN) {
                    // Move to the left lane: Turn right part until both IRs have the same distance to obstacle.
                    m_vehicleControl.setSpeed(SPEED_SLOW);
                    m_vehicleControl.setSteeringWheelAngle(10);

                    // State machine measuring: Both IRs need to have the same distance before leaving this moving state.
                    stageMeasuring = HAVE_BOTH_IR_SAME_DISTANCE;

                    stageToRightLaneLeftTurn++;
                }
                else if (stageMoving == CONTINUE_ON_LEFT_LANE) {
                    // Move to the left lane: Passing stage.
                    m_vehicleControl.setSpeed(SPEED_FAST);
                    m_vehicleControl.setSteeringWheelAngle(0);

                    // Find end of object.
                    stageMeasuring = END_OF_OBJECT;
                }
                else if (stageMoving == TO_RIGHT_LANE_RIGHT_TURN) {
                    // Move to the right lane: Turn right part.
                    m_vehicleControl.setSpeed(SPEED_SLOW);
                    m_vehicleControl.setSteeringWheelAngle(10);

                    stageToRightLaneRightTurn--;
                    if (stageToRightLaneRightTurn < -10) {
                        stageMoving = TO_RIGHT_LANE_LEFT_TURN;
                    }
                }
                else if (stageMoving == TO_RIGHT_LANE_LEFT_TURN) {
                    // Move to the left lane: Turn left part.
                    m_vehicleControl.setSpeed(SPEED_SLOW);
                    m_vehicleControl.setSteeringWheelAngle(-10);

                    stageToRightLaneLeftTurn--;
                    if (stageToRightLaneLeftTurn < 30) {
                        // Start over.
                        stageMoving = FORWARD;
                        overtake = false;
                        stageMeasuring = FIND_OBJECT_INIT;

                        distanceToObstacle = 0;
                        distanceToObstacleOld = 0;
                    }
                }
                

                // Measuring state machine.
                if (stageMeasuring == FIND_OBJECT_INIT) {
                    distanceToObstacleOld = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);
                    stageMeasuring = FIND_OBJECT;
                }
                else if (stageMeasuring == FIND_OBJECT) {
                    distanceToObstacle = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);

                    // Approaching an obstacle (stationary or driving slower than us).
                    if ( (distanceToObstacle > 0) && (((distanceToObstacleOld - distanceToObstacle) > 0) || (fabs(distanceToObstacleOld - distanceToObstacle) < 1e-2)) ) {
                        // Check if overtaking shall be started.
                        stageMeasuring = FIND_OBJECT_PLAUSIBLE;
                    }

                    distanceToObstacleOld = distanceToObstacle;
                }
                else if (stageMeasuring == FIND_OBJECT_PLAUSIBLE) {
                    if (sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) < OVERTAKING_DISTANCE && distanceToObstacleOld < OVERTAKING_DISTANCE ) {
                        stageMoving = TO_LEFT_LANE_LEFT_TURN;
                        overtake = true;
                        cerr << "===========================OVERTAKE=================="  << endl;

                        // Disable measuring until requested from moving state machine again.
                        stageMeasuring = DISABLE;
                    }
                    else {
                        stageMeasuring = FIND_OBJECT;
                    }
                }
                else if (stageMeasuring == HAVE_BOTH_IR) {
                    // Remain in this stage until both IRs see something.
                    if ( (sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT) > 0) && (sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT) > 0) ) {
                        // Turn to right.
                        stageMoving = TO_LEFT_LANE_RIGHT_TURN;
                    }
                }
                else if (stageMeasuring == HAVE_BOTH_IR_SAME_DISTANCE) {
                    // Remain in this stage until both IRs have the similar distance to obstacle (i.e. turn car)
                    // and the driven parts of the turn are plausible.
                    const double IR_FR = sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT);
                    const double IR_RR = sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT);

                    if ((fabs(IR_FR - IR_RR) < HEADING_PARALLEL) && ((stageToRightLaneLeftTurn - stageToRightLaneRightTurn) > 0)) {
                    // if ((fabs(IR_FR - IR_RR) < HEADING_PARALLEL)) {
                        // Straight forward again.
                        stageMoving = CONTINUE_ON_LEFT_LANE;
                    }
                }
                else if (stageMeasuring == END_OF_OBJECT) {
                    // Find end of object.
                    distanceToObstacleOld = distanceToObstacle;
                    distanceToObstacle = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT);

                    if (distanceToObstacle < 0 && distanceToObstacle < 0) {
                        // Move to right lane again.
                        stageMoving = TO_RIGHT_LANE_RIGHT_TURN;

                        // Disable measuring until requested from moving state machine again.
                        stageMeasuring = DISABLE;
                    }
                }
                


                // Create container for finally sending the set values for the control algorithm.
                Container c2(m_vehicleControl);
                // Send container.
                getConference().send(c2);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

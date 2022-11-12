#include <stdio.h>
#include <stdlib.h>

#define SEGMENT_WIDTH 1

// global variable
unsigned long long int penalty = 0;

// function prototypes
int** runFiveFrames(int* lightControl);
int** runFrame(int* lightControl);

void moveThroughIntersection(int* lightControl, int** intersection);
void moveUpLane(int* lightControl, int** intersection, int lane_no);
int checkCollision(int** intersection, int laneOne, int laneTwo);

void checkTraffic(int** intersection, int laneOne, int laneTwo);

void movePedestrians(int* lightControl, int** intersection);
void checkTrafficPedestrians(int** intersection, int laneOne, int laneTwo);

int framePenalty(int** intersection);

int emergencyVehiclePath(int** intersection, int laneOne, int laneTwo);
int emergencyVehiclePresent(int** intersection, int laneOne, int laneTwo);

//hello world

// intersection =
// {
//      {
            // {
                // {is_car, speed, acceleration, turn_left, turn_right, turn_straight, emergency_vehicle, time_waiting}, // one segment
            // } // one lane
//      } * 4 // four lanes
// }
#include <stdio.h>
#include <stdlib.h>

#define SEGMENT_WIDTH 1



// global variable
unsigned long long int penalty = 0;

int*** genIntersection(int streetOne, int streetTwo, int streetThree, int streetFour) {
    int*** intersection = (int**)malloc(sizeof(int**) * 4);
    intersection[0] = (int*)calloc(streetOne, sizeof(int*));
    intersection[1] = (int*)calloc(streetTwo, sizeof(int));
    intersection[2] = (int*)calloc(streetThree, sizeof(int));
    intersection[3] = (int*)calloc(streetFour, sizeof(int));

    int i;
    for (i=0; i<streetOne; i++) {
        // is_car, speed, acceleration, turn_left, turn_right, turn_straight, emergency_vehicle, time_waiting
        intersection[0][i] = (int*)calloc(8, sizeof(int));
    }
    for (i=0; i<streetTwo; i++) {
        intersection[1][i] = (int*)calloc(8, sizeof(int));
    }
    for (i=0; i<streetThree; i++) {
        intersection[2][i] = (int*)calloc(8, sizeof(int));
    }
    for (i=0; i<streetFour; i++) {
        intersection[3][i] = (int*)calloc(8, sizeof(int));
    }

    return intersection;
}

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



// intersection =
// {
//      {
            // {
                // {is_car, speed, acceleration, turn_left, turn_right, turn_straight, emergency_vehicle, time_waiting}, // one segment
            // } // one lane
//      } * 4 // four lanes
// }
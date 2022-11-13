#ifndef MAIN_H
#define MAIN_H

// include the header file of the individual function files
#include "calcAcceleration.h"
#include "calcFollowDistance.h"
#include "checkTraffic.h"
#include "checkTrafficPedestrians.h"
#include "flatten.h"
#include "framePenalty.h"
#include "freeCar.h"
#include "movePedestrians.h"
#include "moveUpLane.h"
#include "spawnCar.h"
#include "updateIntersection.h"

// width of a segment of road, 1 ft by default
#define SEGMENT_WIDTH 1
#define FPS 15
// 45 mph speed limit
#define SPEED_LIMIT 66
// 15 mph turning average
#define TURNING_SPEED 22

//      #####
//      #####
//      ##1##
// ###############
// ####0#####2####
// ###############
//      ##3##
//      #####
//      #####

typedef struct car {
    unsigned int distance; // distance from the intersection to the front of the car (Not a char to allow for higher values than 255)
    // following are chars to save space
    char length; // length of the car
    char speed; // speed of the car
    char acceleration; // acceleration of the car
    char direction; // direction the car is turning, 0 for straight, 1 for left, 2 for right
    char maxAcceleration; // maximum acceleration of the car
    char maxDeceleration; // maximum deceleration of the car, usually higher than maxAcceleration. Positive value (convert to negative when used)
    unsigned timeWaiting; // time the car has been waiting at the intersection
        // for 2 bytes, this imposes a limit of 65,535 frames, or (with 15 FPS) 4,369 seconds, or 72.82 minutes, or 1.21 hours
        // as it is unlikely for a car to wait at an intersection for more than 1 hour, this should be fine
        // only counts the time the car has had speed 0. Resets to 0 when the car starts moving
    struct car* carBehind; // pointer to the car behind this car
} car;

// global variable ===============================================

unsigned long long int penalty = 0;
unsigned long int second = 0;
// file with the spawn data, in chronological order
FILE *spawnFile;
// 3d array of the intersection
int*** intersection;

// global lengths of the streets =================================

int streetOneLength;
int streetTwoLength;
int streetThreeLength;
int streetFourLength;

// global linked list of cars for each lane ======================

car* laneOne = NULL;
car* laneTwo = NULL;
car* laneThree = NULL;
car* laneFour = NULL;
car** linkedListIntersection = NULL;

// global waiting queue for each lane (linked list) ==============

car* laneOneWaiting = NULL;
car* laneTwoWaiting = NULL;
car* laneThreeWaiting = NULL;
car* laneFourWaiting = NULL;

// pedestrian crossing ===========================================

// number of pedestrians in each lane. Goes in this pattern
        // from to
        // 0: 0 1
        // 1: 0 3
        // 2: 1 2
        // 3: 1 0
        // 4: 2 3
        // 5: 2 1
        // 6: 3 0
        // 7: 3 2
    // i/2 is the lane the pedestrian is in
    // i%2==0 ? (i+1) % 4 : (i-1) % 4; is the lane the pedestrian is going to
char pedestrianCrossing[8] = {'\0'};
char pedestrianWaiting[8] = {'\0'};

// intersection extra data ======================================

// 4 roads * [active car in lane, time_car_in_lane, active pedestrian crossing] * in/out lanes (2)
// lane*6 + 0: active car in outgoing lane
// lane*6 + 1: time_car_in_lane in outgoing lane
// lane*6 + 2: active pedestrian crossing in outgoing lane
// lane*6 + 3: active car in incoming lane
// lane*6 + 4: time_car_in_lane in incoming lane
// lane*6 + 5: active pedestrian crossing in incoming lane
char intersectExtra[4*3*2] = {'\0'};

// extra ========================================================

// global heap for misc values and data
// 0 -> lane 0's yellow light time
// 1 -> lane 1's yellow light time
// 2 -> lane 2's yellow light time
// 3 -> lane 3's yellow light time
// 4 -> fractional penalty var (modulo) lane 1
// 5 -> fractional penalty var (modulo) lane 2
// 6 -> fractional penalty var (modulo) lane 3
// 7 -> fractional penalty var (modulo) lane 4
int heap[64] = {0};

// function prototypes ==========================================

// runs FPS # of frames, calls flatten at the end
int* runOneSecond(int** lightControl);
// reads from a file and spawns cars if it can, otherwise add to waitingQueue
void spawnCar(car** linkedListIntersection);
// updates the intersection with the cars in the linked list. Run at the end of one second
void updateIntersection(car** linkedListIntersection, int*** intersection);
// flattens the intersection into a 1D array for AI processing
int* flatten(int*** intersection);

// void moveThroughIntersection(int** lightControl, car** linkedListIntersection);

// updates each vehicle in each lane with a new position, speed, and acceleration
// based on lightControl, distance to next car, speed limit, and more advanced
// cases such as turning speeds at a green light and etc. Checks waiting queue
// and sees if the length of the end of the lane can fit the next waiting car
// (if present) plus following distance based on speed
void moveUpLane(int** lightControl, car** linkedListIntersection);

// checks lanes for oncoming traffic to see if a right-on-red turn is possible
// looks at the next car in the lane with the green light, and compares distance
// vs speed
int checkTraffic(car** linkedListIntersection, int laneOne, int laneTwo); 
// checks opposite lane for incoming traffic (if other is red) to see if
// a left turn is possible. Otherwise car will stall in the intersection
int checkLeftTurn(car** linkedListIntersection, int laneOne, int laneTwo);

// Checks if pedestrians are safe to cross (no cars coming OR walk light, part of lightControl)
// If so, moves pedestrians across the street
void movePedestrians(int** lightControl);
// helper function of movePedestrians to check if no cars are coming
void checkTrafficPedestrians(car** linkedListIntersection, int laneOne);

// checks how long cars and pedestrians have been waiting at the intersection
// also adds severe penalties for accidents
long double framePenalty(car** linkedListIntersection, char* pedestrianCrossing, char* pedestrianWaiting, char* intersectExtra);

// calculates the following distance of a car based on speed of current car and next car
//then multiplying it by the time we want cars separated by
int calcFollowDistance(car* currCar, car* nextCar);

// calculate the required acceleration. Returns signed value of acceleration
// (negative -> slow down, positive -> speed up)
// if light is green, then bases accerlation off of followDistance vs actual distance
//    if it's about to enter the intersection and needs to turn, it will calculate
//    the required deceleration to reach the turning speed
// if light is yellow, then looks at the time the light has been yellow, and if it
//    if it can make it and the car ahead of it isn't slowing down, it will speed up
//    if it's going to turn, we need to calculate the required speedup & the required
//    deceleration, and the time required for both, and if the vehicle can make it
// if light is red, take the min negative deceleration between needed for following
//    distance and the deceleration needed to stop at the red light (taking into)
//    account the length of vehicles ahead). Deceleration cannot be more than
//    maxDeceleration
// RETURNS FEET PER SECOND SQUARED
int calcAcceleration(int** lightControl, car* currCar, car* nextCar, int followDistance, int lane);


// free car after it reaches exit lane
void freeCar(car* car);
#endif // MAIN_H
#include <stdio.h>
#include <stdlib.h>
// include the header file of the individual function files

// width of a segment of road, 1 ft by default
#define SEGMENT_WIDTH 1
#define FPS 15
// 45 mph speed limit
#define SPEED_LIMIT 66
// 15 mph turning average
#define TURNING_SPEED 22

typedef struct {
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
    car* carBehind; // pointer to the car behind this car
} car;

// global variable ===============================================

unsigned long long int penalty = 0;
unsigned long int second = 0;

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
char intersectExtra[4*3*2] = {'\0'};

// extra ========================================================

// global heap for misc values and data
int heap[100];

// function prototypes ==========================================

// runs FPS # of frames, calls flatten at the end
int* runOneSecond(int** lightControl);
// reads from a file and spawns cars if it can, otherwise add to waitingQueue
void spawnCar(car** linkedListIntersection);
// updates the intersection with the cars in the linked list. Run at the end of one second
int*** updateIntersection(car** linkedListIntersection);
// flattens the intersection into a 1D array for AI processing
int* flatten(int*** intersection);

// void moveThroughIntersection(int** lightControl, car** linkedListIntersection);

// updates each vehicle in each lane with a new position, speed, and acceleration
// based on lightControl, distance to next car, speed limit, and more advanced
// cases such as turning speeds at a green light and etc. Checks waiting queue
// and sees if the length of the end of the lane can fit the next waiting car
// (if present) plus following distance based on speed
void moveUpLane(int** lightControl, car** linkedListIntersection);
// returns 1 if vehicle collision, 2 if pedestrian collision, 0 otherwise
int collision(car* car, char* intersectExtra, char* pedestrianCrossing);

// checks lanes for oncoming traffic to see if a right-on-red turn is possible
// looks at the next car in the lane with the green light, and compares distance
// vs speed
void checkTraffic(car** linkedListIntersection, int laneOne, int laneTwo); 

// Checks if pedestrians are safe to cross (no cars coming OR walk light, part of lightControl)
void movePedestrians(int** lightControl, char* pedestrianCrossing);
// helper function of movePedestrians to check if no cars are coming
void checkTrafficPedestrians(car** linkedListIntersection, int laneOne, int laneTwo);

// checks how long cars and pedestrians have been waiting at the intersection
// also adds severe penalties for accidents
int framePenalty(car** linkedListIntersection, char* pedestrianCrossing, char* pedestrianWaiting, char* intersectExtra);

// calculates the following distance of a car based on integer division by
// 10, then that in seconds (multipled by speed/second). Returns in SEGMENT_WIDTH
int calcFollowDistance(int speed, car* currCar, car* nextCar);

// calculate the required deacceleration. Returns signed value of deacceleration
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
int calcDeceleration(int** lightControl, car* currCar, car* nextCar, int followDistance, int lane);


// free car after it reaches exit lane
void freeCar(car* car);




// run once at the beginning of the program, returns point to 3d array representing the intersection
int*** init(int streetOne, int streetTwo, int streetThree, int streetFour) {
    // inits the linkedListIntersection array
    linkedListIntersection = (car**)malloc(sizeof(car*) * 4);
    linkedListIntersection[0] = laneOne;
    linkedListIntersection[1] = laneTwo;
    linkedListIntersection[2] = laneThree;
    linkedListIntersection[3] = laneFour;

    // inits the intersection array
    streetOneLength = streetOne;
    streetTwoLength = streetTwo;
    streetThreeLength = streetThree;
    streetFourLength = streetFour;
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

int* runOneSecond(int** lightControl) { // python will run this function 86400 times (24 hours * 60 minutes * 60 seconds)
    int i;
    for (i=0; i<FPS; i++) {
        spawnCar(linkedListIntersection);
        moveUpLane(lightControl, linkedListIntersection);
        movePedestrians(lightControl, pedestrianCrossing);
        penalty += framePenalty(linkedListIntersection, pedestrianCrossing, pedestrianWaiting, intersectExtra);
    }
    return flatten(updateIntersection(linkedListIntersection));
}
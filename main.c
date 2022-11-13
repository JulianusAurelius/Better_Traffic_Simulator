#include <stdio.h>
#include <stdlib.h>
// include the header file of the individual function files
#include "main.h"

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
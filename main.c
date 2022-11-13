#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// run once at the beginning of the program, returns point to 3d array representing the intersection
int*** init(int streetOne, int streetTwo, int streetThree, int streetFour) {
    // inits the linkedListIntersection array
    linkedListIntersection = (car**)malloc(sizeof(car*) * 4);
    linkedListIntersection[0] = laneOne;
    linkedListIntersection[1] = laneTwo;
    linkedListIntersection[2] = laneThree;
    linkedListIntersection[3] = laneFour;

    // opens the spawn file
    spawnFile = fopen("spawn.txt", "r");
    if (spawnFile == NULL) {
        printf("Error opening spawn file");
        exit(-1);
    }

    // inits the intersection array
    streetOneLength = streetOne;
    streetTwoLength = streetTwo;
    streetThreeLength = streetThree;
    streetFourLength = streetFour;
    int*** intersection = (int***)malloc(sizeof(int**) * 4);
    intersection[0] = (int**)calloc(streetOne, sizeof(int*));
    intersection[1] = (int**)calloc(streetTwo, sizeof(int));
    intersection[2] = (int**)calloc(streetThree, sizeof(int));
    intersection[3] = (int**)calloc(streetFour, sizeof(int));

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

int* flatIntersectionInit() {
    int* flatIntersection = (int*)malloc(sizeof(int) * (streetOneLength + streetTwoLength + streetThreeLength + streetFourLength) * 8);
    return flatIntersection;
}

int* runOneSecond(int** lightControl) { // python will run this function 86400 times (24 hours * 60 minutes * 60 seconds)
    // might need to be given a 1d array of the light control, then convert
    // pedestrian light = pl
    // [
    //      [green, yellow, red], // lane 1
    //      [green, yellow, red], // lane 2
    //      [green, yellow, red], // lane 3
    //      [green, yellow, red]  // lane 4
    //      [pl1, pl2, pl3] // pedestrian lights
    //      [pl4, pl5, pl6] // pedestrian lights
    //      [pl7, pl8, null] // pedestrian lights
    // ]
    // if we are given a 1d array first, then convert,
    // we could make a 2d array of the light control,
    // and then make a 1d array of the pedestrian lights
    // 2 separate arrays


    int i;
    for (i=0; i<FPS; i++) {
        spawnCar(linkedListIntersection);
        moveUpLane(lightControl, linkedListIntersection);
        movePedestrians(lightControl);
        penalty += framePenalty(linkedListIntersection, pedestrianCrossing, pedestrianWaiting, intersectExtra);
    }
    heap[4] = (heap[4]++)%4; // slowing down has a quarter of the cost of slowing down

    // TODO: set heap[4+lane#] to 0 if light not yellow, else increment
    
    // write linked list data to output file
    updateIntersection(linkedListIntersection, intersection);
    return flatten(intersection, flatIntersection);
}

void end() { // run once at the end of the program
    
    // free memory
    // Might need work
    int i;
    for (i=0; i<streetOneLength; i++) {
        free(intersection[0][i]);
    }
    for (i=0; i<streetTwoLength; i++) {
        free(intersection[1][i]);
    }
    for (i=0; i<streetThreeLength; i++) {
        free(intersection[2][i]);
    }
    for (i=0; i<streetFourLength; i++) {
        free(intersection[3][i]);
    }
    
    free(intersection[0]);
    free(intersection[1]);
    free(intersection[2]);
    free(intersection[3]);

    free(intersection);

    // free linked list if needed
    while (laneOne != NULL) {
        car* temp = laneOne;
        laneOne = laneOne->carBehind;
        free(temp);
    }
    while (laneTwo != NULL) {
        car* temp = laneTwo;
        laneTwo = laneTwo->carBehind;
        free(temp);
    }
    while (laneThree != NULL) {
        car* temp = laneThree;
        laneThree = laneThree->carBehind;
        free(temp);
    }
    while (laneFour != NULL) {
        car* temp = laneFour;
        laneFour = laneFour->carBehind;
        free(temp);
    }
    // free linked list intersection
    free(linkedListIntersection);

    // close file
    fclose(spawnFile);
}
#include "movePedestrians.h"

void movePedestrians(int** lightControl) {
    // pedestrianCrossing counts number of people waiting
    // pedestrianWaiting counts time spent waiting
    // intersectExtra counts number of people crossing

    // loop through pedestrianCrossing (8 elements)
    for (int i=0; i<8; i++) {
        if (intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 2]) {
            // unrealistic, needs improvement, but for simplicty, assume
            // crossing in 1 second
            intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 2] = 0;
            intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 5] = 0;
        }
        if (!pedestrianCrossing[i]) {
            continue;
        }
        // check traffic on the two lanes
        // see if active (use i%2==0 ? (i+1) % 4 : (i-1) % 4)
        if (intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4] || intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 3]) {
            // car in the lane
            continue;;
        }
        // if not checkTrafficPedestrian
        if (!checkTrafficPedestrian(i)) {
            // move the pedestrian
            // set crossing to num of people
            intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 2] = pedestrianCrossing[i];
            intersectExtra[i%2==0 ? (i+1) % 4 : (i-1) % 4 + 5] = pedestrianCrossing[i];
            // set pedestrian waiting to 0
            pedestrianWaiting[i] = 0;
            // set pedestrian crossing to 0
            pedestrianCrossing[i] = 0;
        }
        // else
        else {
            // increment pedestrian waiting
            pedestrianWaiting[i]++;
        }
    }
}
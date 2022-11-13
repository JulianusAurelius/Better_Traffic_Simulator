#include "spawnCar.h"


void spawnCar(car** linkedListIntersection) {
    // check if current line's first item (and integer, up to the space) matches the second
    // if it does, then read the other tokens
        // if the next token is a 1,
            // create a new car
                // see if the spawn lane has enough room (with following distance, but speed can be
                // adjusted to make it work, if need be, as long as the speed is equal to the car
                // in front of it)
                    // if it does, then append the car to the end of the linked list
                // else
                    // add the car to the waiting queue for that lane
        // else
            // spawn a pedestrian (there will be a single integer after, for which intersection to spawn at)
            // simply increment pedestrianWaiting at that intersection. If pedestrianWaiting is 254, then keep it at 254
    // else
        // SEEK back to the beginning of the line
            // this might be difficult. We might need to keep track of where
            // we are in the file, and then seek back to that position
}
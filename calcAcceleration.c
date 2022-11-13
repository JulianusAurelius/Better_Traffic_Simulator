#include "calcAcceleration.h"

int calcAcceleration(int** lightControl, car* currCar, car* nextCar, int followDistance, int lane) {
    if (currCar == NULL) {
        return 0;
    }
    // startPos
    // endPos
    // check if curr car is NULL, if so calculate distance as the distance of nextCar's rear bumper to the end of the lane
        // CHANGE: We return is the car is NULL
    // if nextCar is NULL, calculate the distance as the distance of currCar's front bumper to the intersection
    int startPos = currCar->distance;
    // if (startPos == -1) {
    //     switch (lane) {
    //         case 0:
    //             startPos = streetOneLength;
    //             break;
    //         case 1:
    //             startPos = streetTwoLength;
    //             break;
    //         case 2:
    //             startPos = streetThreeLength;
    //             break;
    //         case 3:
    //             startPos = streetFourLength;
    //             break;
    //     }
    // }
    int endPos = nextCar == NULL ? 0 : nextCar->distance + nextCar->length;
    int distance = startPos - endPos;

    char canPositive = 1;

    // if the car is in front, and the light has been yellow for more than 3 seconds, the acceleration cannot be positive. Or if the intersection is active
    if ((nextCar == NULL & heap[4+lane] > 3*FPS) || (intersectExtra[lane*6+2] || intersectExtra[ (currCar->direction==2 ? lane-1 : lane+currCar->direction)%4*6+3 ] ) ) {
        canPositive = 0;
    } else if (lightControl[lane][1] == 1) { //yellow
        // see if the car can reach light before the light has been yellow for more than 3 seconds with max acceleration
        int speed1 = currCar->speed;
        int speed2 = currCar->speed + currCar->maxAcceleration * (heap[4+lane] - 3*FPS) / FPS;
        int avgSpeed = (speed1 + speed2) / 2;
        int distanceCanTravel = avgSpeed * (heap[4+lane] - 3*FPS) / FPS;
        int distanceToLight = distance;
        // int requiredAccel = (int)(
        //     // a = maxAccel
        //     // v1 = car->speed
        //     // v2 = (2*distance)^(1/2)
        //     (float) 
        // )
        // if the required acceleration is greater than the max acceleration, then the acceleration cannot be positive
        if (distanceCanTravel < distanceToLight) {
            canPositive = 0;
        } else {
            return currCar->maxAcceleration;
        }
    }
    // if the distance to the next car is less than the follow distance, then the acceleration cannot be positive
    if (distance < followDistance) {
        canPositive = 0;
    }
    // if the car is in front, and the light is red, calculate a negative acceleration to stop at the red light
    if (nextCar == NULL && lightControl[lane][2] == 1) {
        // Assume average slowdown deceleration is -5 ft/s^2
        float timeToStop = pow((distance)/-5.0, 0.5); // time to stop in seconds
        int feetToStop = (int)(currCar->speed/2 * timeToStop); // average speed between speed and 0 is speed/2
        if (feetToStop < distance + 15 ) { // if it can stop within 15 feet of the light
            return -5; // decelerate at 5 ft/s^2
        }

    }
    
    int decel = 0;
    // if the car is in front, the light is green, and the car is turning, calculate the required acceleration
    if (nextCar == NULL && currCar->direction != 0) {
        int endVelocity = TURNING_SPEED;
        int currVelocity = currCar->speed;
        int distanceToTurn = distance;
        int avgVelocity = (currVelocity + endVelocity) / 2;
        int time = distanceToTurn/avgVelocity;
        decel = (currVelocity - endVelocity) / time; // should preserve sign for positive or negative acceleration
    }
    // or deceleration to reach the turning speed

    // if acceleration can be positive, and the distance to the next car is greater than the follow distance,
    // if (canPositive && distance > followDistance) {
    //     // int difference = distance - followDistance;
    //     // for now just return 3, ~2 ft/s^2
    //     // if (decel == 0) {
    //     //     return 3;
    //     // }
    // }
    // then speed up at the normal acceleration rate to the speed limit
    // for now just return 3, ~2 ft/s^2
    return decel ? decel : 3;
}

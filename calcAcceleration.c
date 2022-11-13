#include "calcAcceleration.h"

int calcAcceleration(int** lightControl, car* currCar, car* nextCar, int followDistance, int lane) {
    // startPos
    // endPos
    // check if curr car is NULL, if so calculate distance as the distance of nextCar's rear bumper to the end of the lane
    // if nextCar is NULL, calculate the distance as the distance of currCar's front bumper to the intersection

    // if the car is in front, and the light has been yellow for more than 3 seconds, the acceleration cannot be positive
        // else calculate the required acceleration to reach the light by the 3rd second
        // if the required acceleration is greater than the max acceleration, then the acceleration cannot be positive
    // if the distance to the next car is less than the follow distance, then the acceleration cannot be positive
    // if the car is in front, and the light is red, calculate a negative acceleration to stop at the red light
    
    // if the car is in front, the light is green, and the car is turning, calculate the required acceleration
    // or deceleration to reach the turning speed

    // if acceleration can be positive, and the distance to the next car is greater than the follow distance,
    // then speed up at the normal acceleration rate to the speed limit
}

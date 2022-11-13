#include "moveUpLane.h"

car* moveUpLaneHelper1(car* lane, int laneNum, int isGreen); // can move through intersection
car* moveUpLaneHelper2(car* lane, int light); // can't move through intersection

// returns 1 if vehicle collision, 2 if pedestrian collision, 0 otherwise
int collision(car* car, int lane1, int lane2);


void moveUpLane(int** lightControl, car** linkedListIntersection) {
    // move up green & yellow lanes first
    if (lightControl[0][0] == 1 || lightControl[0][1] == 1) {
        linkedListIntersection[0] = moveUpLaneHelper1(linkedListIntersection[0], 0, lightControl[0][0]);
    }
    if (lightControl[1][0] == 1 || lightControl[1][1] == 1) {
        linkedListIntersection[1] = moveUpLaneHelper1(linkedListIntersection[1], 1, lightControl[1][0]);
    }
    if (lightControl[2][0] == 1 || lightControl[2][1] == 1) {
        linkedListIntersection[2] = moveUpLaneHelper1(linkedListIntersection[2], 2, lightControl[2][0]);
    }
    if (lightControl[3][0] == 1 || lightControl[3][1] == 1) {
        linkedListIntersection[3] = moveUpLaneHelper1(linkedListIntersection[3], 3, lightControl[3][0]);
    }

    // move up red lanes
    if (lightControl[0][3] == 0) {
        linkedListIntersection[0] = moveUpLaneHelper2(linkedListIntersection[0], 2);
    }
    if (lightControl[1][3] == 0) {
        linkedListIntersection[1] = moveUpLaneHelper2(linkedListIntersection[1], 2);
    }
    if (lightControl[2][3] == 0) {
        linkedListIntersection[2] = moveUpLaneHelper2(linkedListIntersection[2], 2);
    }
    if (lightControl[3][3] == 0) {
        linkedListIntersection[3] = moveUpLaneHelper2(linkedListIntersection[3], 2);
    }
}

car* moveUpLaneHelper1(car* lane, int laneNum, int isGreen) {
    // remember speed is feet/second, divide by FPS to get feet/frame

    // TODO: adjust algorithm to check if the car is going to make a left turn
        // if they are, check if there's oncoming traffic using checkLeftTurn
        // if there is traffic, have the car slow down to a stop, and wait in the
        // intersection until the traffic clears
        // Also, need to check if the car currently in the intersection (if any)
        // is waiting for clear traffic to make a left turn. Once the traffic
        // is clear, calculate a new time_in_intersection based on the double
        // derivative of the car's max acceleration, and the time it will take
        // to reach 20 ft.

    // make temp lane head
    // take care of intersection first
    // if intersection isn't empty
        // decrement time_waiting for cars in intersection
        // if time_waiting == 0
            // make lane point to next car, and despawn the previous car
            // reset intersection data for those 2 lanes
        // skip temp lane head ahead to next car
    
    // if next vehicle can move through intersection
        // if there's another car in the intersection
            // collision and despawn 2nd car
        // else
            // speed, acceleration, and position
            // move car into intersection
    
    // call moveUpLaneHelper2 on temp lane head w/ argument of isGreen
    
    // return lane head
}

car* moveUpLaneHelper2(car* lane, int light) {
    // remember speed is feet/second, divide by FPS to get feet/frame

    // simple move vehicles up and decelerate to a stop if need be

    int temp_flag = 0;

    // loop through lane
        // adjust speed, acceleration, and position
        // if no car ahead & intersection is empty & light is green
            // maintain speed
        // if no car ahead & intersection is empty & light is yellow
            // calculate time to intersection (if turning, take into account time it takes to decelerate to turnin speed)
                // if time to intersection < 2 seconds
                    // accelerate 
                // else
                    // decelerate
        // if no car ahead & intersection is empty & light is red
            // calculate if car will decelerate to a stop within 5 feet of intersection
                // if yes
                    // decelerate
                    // set temp_flag to 1
                    // increment time_stopped by 1 if heap[4] == 0
                // else
                    // maintain speed until closer
            // if already within 5 feet of intersection
                // go at 1 segment/frame until at intersection
        // if car ahead
            // calculate following distance
            // calculate acceleration needed to maintain following distance
                // (negative means slow down, positive means speed up)
        // if car was stopped and remains stopped, increment time_stopped
            // set temp_flag to 1
        
        // if not temp_flat
            // reset time_stopped to 0
        
    
    // if light is red, front car is stopped, and is going to turn right
        // run checkTraffic to see if a car is coming that may hit it
            // if no, turn right on red
                // despawn car, move head of lane to next car
    
    // return lane head
}

int collision(car* car, int lane1, int lane2) {
    if (
        intersectExtra[lane1*6]   ||
        intersectExtra[lane2*6+3] ||
        intersectExtra[lane1*6+1] ||
        intersectExtra[lane2*6+4]
    ) { // vehicle collision
        // call write function to write collision info
        penalty += 200.0;
        return 1;
    }


    else if (
        intersectExtra[lane1*6+2] ||
        intersectExtra[lane2*6+5]
    ) { // pedestrian collision
        // call write function to write collision info
        penalty += intersectExtra[lane1*6+2] ? 150.0*intersectExtra[lane1*6+2] : 150.0*intersectExtra[lane2*6+5];
        return 2;
    }

    // no collision
    return 0;
}
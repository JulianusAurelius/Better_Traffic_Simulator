#include "calcFollowDistance.h"

int calcFollowDistance(car* currCar, car* nextCar) {
    int followDistanceOutput;
    // following distance should be 5 seconds
    // multiply speed by SEPARATION_TIME to get distance (feet/s)
    if((currCar==NULL)&&(nextCar==NULL)){
        // if both cars are NULL, use the speed limit
        return SPEED_LIMIT*SEPARATION_TIME;
    }
    else if(nextCar==NULL){
        // if the second car is NULL, use the first car's speed
        followDistanceOutput = currCar->speed*SEPARATION_TIME;
        return followDistanceOutput;
    }
    else if(currCar==NULL){
        // if the first car is NULL, use the second car's speed
        followDistanceOutput = nextCar->speed*SEPARATION_TIME;
        return followDistanceOutput;
    }
    else{
        //if both cars then we take the average speed of both cars and multipy times 5
        followDistanceOutput = ((currCar->speed+nextCar->speed)/2)*SEPARATION_TIME;
        return followDistanceOutput;
    }
    
}

#include "framePenalty.h"

long double framePenalty(car** linkedListIntersection, char* pedestrianCrossing, char* pedestrianWaiting, char* intersectExtra) {
    // follow a penalty system of the following
        // Sum of the following (loop through both linked lists)
            // each car's time waiting is i
            // (2^(i/(15*10))) / 50
        // for pedestrian waiting time, add 1.1^(i/(15*2)) * #ofPeople (at that intersection)
    // return the penalty
}
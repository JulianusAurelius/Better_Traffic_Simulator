#include "flatten.h"

int* flatten(int*** intersection) {
    // malloc ( #ofLanes * #ofSegments * 8 * sizeof(int) )
    // init i=0;
    // loop through the intersection, and add each element to the array
        // use loop unrolling to speed up the process
        // and since the segments are always 8 integers
}
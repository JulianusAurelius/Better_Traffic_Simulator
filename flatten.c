#include "flatten.h"

int* flatten(int*** intersection, int* flatIntersection) {
    // malloc ( #ofLanes * #ofSegments * 8 * sizeof(int) )
    // init i=0;
    // loop through the intersection, and add each element to the array
        // use loop unrolling to speed up the process
        // and since the segments are always 8 integers
    
    int length = (streetOneLength + streetTwoLength + streetThreeLength + streetFourLength) * 8;
    int i = 0;
    int j;
    for (j=0; j<streetOneLength; j++) {
        flatIntersection[i]   = intersection[0][j][0];
        flatIntersection[i+1] = intersection[0][j][1];
        flatIntersection[i+2] = intersection[0][j][2];
        flatIntersection[i+3] = intersection[0][j][3];
        flatIntersection[i+4] = intersection[0][j][4];
        flatIntersection[i+5] = intersection[0][j][5];
        flatIntersection[i+6] = intersection[0][j][6];
        flatIntersection[i+7] = intersection[0][j][7];
        i += 8;
    }
    for (j=0; j<streetTwoLength; j++) {
        flatIntersection[i]   = intersection[1][j][0];
        flatIntersection[i+1] = intersection[1][j][1];
        flatIntersection[i+2] = intersection[1][j][2];
        flatIntersection[i+3] = intersection[1][j][3];
        flatIntersection[i+4] = intersection[1][j][4];
        flatIntersection[i+5] = intersection[1][j][5];
        flatIntersection[i+6] = intersection[1][j][6];
        flatIntersection[i+7] = intersection[1][j][7];
        i += 8;
    }
    for (j=0; j<streetThreeLength; j++) {
        flatIntersection[i]   = intersection[2][j][0];
        flatIntersection[i+1] = intersection[2][j][1];
        flatIntersection[i+2] = intersection[2][j][2];
        flatIntersection[i+3] = intersection[2][j][3];
        flatIntersection[i+4] = intersection[2][j][4];
        flatIntersection[i+5] = intersection[2][j][5];
        flatIntersection[i+6] = intersection[2][j][6];
        flatIntersection[i+7] = intersection[2][j][7];
        i += 8;
    }
    for (j=0; j<streetFourLength; j++) {
        flatIntersection[i]   = intersection[3][j][0];
        flatIntersection[i+1] = intersection[3][j][1];
        flatIntersection[i+2] = intersection[3][j][2];
        flatIntersection[i+3] = intersection[3][j][3];
        flatIntersection[i+4] = intersection[3][j][4];
        flatIntersection[i+5] = intersection[3][j][5];
        flatIntersection[i+6] = intersection[3][j][6];
        flatIntersection[i+7] = intersection[3][j][7];
        i += 8;
    }

    return flatIntersection;

}
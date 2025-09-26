#include "closestpair.h"
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>  // used to seed srand for extra credit
using namespace std;

// For convenience, we provide a brute-force implementation that can be applied
// to any portion of a larger sequence by providing start and stop iterators.
template <typename IT>
Outcome bruteUtility(IT start, IT stop) {
    IT second = start;
    ++second;
    Outcome best(*start, *second, distSquared(*start, *second));
    for (IT k=start; k != stop; ++k)
        for (IT j=start; j != k; ++j) {
            long long temp = distSquared(*j, *k);
            if (temp < best.dsq) {
                best = Outcome(*j, *k, temp);
            }
        }
    return best;
}

// The public facing brute-force function that takes a vector as input
Outcome brute(const vector<Point>& data) {
    return bruteUtility(data.begin(), data.end());
}


/*------------------------------------------------------------
| Here we define a cutoff value at which the divide-and-conquer
| approach should resort to a base-case in which brute-force is applied.
| You are free to change this cutoff to optimize, but please make sure
| that the logic of your implementation rely on this defined CUTOFF constant.
--------------------------------------------------------------*/
#define CUTOFF 3          // you may change this, but please 


// The student's implementation of the O(n log n) divide-and-conquer approach
template <typename IT>
Outcome efficientUtility(IT start, IT stop, const vector<Point>& sortedY) {
    // base case of using the brute-force implementation
    if (stop-start <= CUTOFF) {
        return bruteUtility(start, stop);
    }

    // find the midpoint of the sorted x-values
    int dist = stop - start;
    IT mid = start + dist/2;

    // split the sorted y values into left and right
    vector<Point> leftY;
    vector<Point> rightY;
    for (Point p : sortedY) {
        if (compareByX(p, *mid)) {
            leftY.push_back(p);
        } else {
            rightY.push_back(p);
        }
    }

    // find the closest points on the left and right of the midpoint
    Outcome left = efficientUtility(start, mid, leftY);
    Outcome right = efficientUtility(mid, stop, rightY);
    Outcome closest = (left.dsq < right.dsq ? left : right);

    // check within (closest) of the midpoint
    long midX = (*mid).x;

    return closest;
}

Outcome efficient(const vector<Point>& data) {
    vector<Point> sortedDataX(data);
    vector<Point> sortedDataY(data);
    sort(sortedDataX.begin(), sortedDataX.end(), compareByX);
    sort(sortedDataY.begin(), sortedDataY.end(), compareByY);

    return efficientUtility(sortedDataX.begin(), sortedDataX.end(), sortedDataY);
}

// An extra credit algorithm
Outcome extra(const vector<Point>& data) {
    srand(time(NULL));  // re-seeding random number generator
    return Outcome();
}

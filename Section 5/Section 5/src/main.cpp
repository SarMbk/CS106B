#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include <cmath>
#include <limits.h>
using namespace std;


/* Utility function to find sum of all elements of a vector */
int vecSum(Vector<int> &v){
    int sum = 0;
    for (int i=0; i< v.size(); i++)
        sum+=v[i];
    return sum;
}


/* Finds all possible subvectors and prints a subvector such that the sum of its elements produce the greatest number. Runs in O(N^3) */
void maxSubVecSum(Vector<int> &v){
    Vector< Vector<int> > allSubvecs;

    // Find all subvectors and populate allSubvecs with them
    for (int i=0; i <v.size(); i++){
        for (int j=i; j<v.size(); j++){
            Vector<int> subvec;
            for (int k=i; k<=j; k++){
                subvec.add(v[k]);
            }
            allSubvecs.add(subvec);
        }
    }

    // Find a subvector that gives the maximum sum
    int max =vecSum(allSubvecs[0]); int maxIndex;
    for (int i=0; i<allSubvecs.size(); i++){
        if (vecSum(allSubvecs[i]) > max){
            max = vecSum(allSubvecs[i]);
            maxIndex = i;
        }
    }

    cout << "Max subvector sum: " << max << "; From subvector: " << allSubvecs[maxIndex]<< endl;
}


/* This function does not give the right result when the last element is negative. Runs in O(N^2) */
void subVecMaxO2(Vector<int> &v){
    int maxSofar = 0;
    for (int i=0; i<v.size(); i++){
        int sum = 0;
        for (int j=i; j<v.size(); j++)
            sum= sum + v[j];
        maxSofar = max(sum, maxSofar);
    }
    cout << maxSofar <<endl;
}


/* This function recursively finds max subvector sum. Runs in linearithmic time. O(NlogN) */
int recMaxSubVecSum(Vector<int> &v, int lh, int rh){
    // Zero element (empty) vector
    if (lh>rh) return 0;

    // One element vector
    if (lh==rh) return max(0, v[lh]);

    // Left half of the recursion is v[lh...m] right half is v[m+1...rh]
    int m = (lh+rh)/2;

    // Find max touching the border on the left
    int sumLeft = 0;
    int maxToLeft = 0;
    for (int i=m; i>=lh; i--){
        sumLeft+=v[i];
        maxToLeft = max(sumLeft, maxToLeft);
    }

    // Find max touching the border on the right
    int sumRight = 0;
    int maxToRight = 0;
    for (int i=m+1; i<=rh; i++){
        sumRight+=v[i];
        maxToRight = max(sumRight, maxToRight);
    }

    // MaxCrossing is the maximum subvector that crosses the middle border
    int maxCrossing = maxToLeft+ maxToRight;

    int maxLeftHalf = recMaxSubVecSum(v, lh, m);
    int maxRightHalf = recMaxSubVecSum(v, m+1, rh);

    return max(max(maxCrossing, maxLeftHalf), maxRightHalf);
}


/* This function finds max subvector sum with one linear pass. Runs in linear time. O(N) */
int linMaxSubVecSum(Vector<int> &v){
    int maxSoFar = 0;
    int maxEndingHere = 0;
    for (int i=0; i<v.size(); i++){
        maxEndingHere = max(maxEndingHere + v[i], 0);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}



int main()
{
    Vector<int> numbers = {-1, 2, -3, -4, -5, -6, -7, -8};
    maxSubVecSum(numbers);

    int initRh = numbers.size()-1;
    cout << recMaxSubVecSum(numbers, 0, initRh) << endl;
    cout << linMaxSubVecSum(numbers) <<endl;

    return 0;
}


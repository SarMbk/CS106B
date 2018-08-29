#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include <cmath>
using namespace std;



/* Selection Sort Algorithm */
int selectionSort(Vector<int> & vec){
    int n = vec.size();
    for (int i=0; i<n-1; i++){
        int minIndex=i;
        for (int j=i+1; j<n; j++){
            if (vec[j] < vec[minIndex]) minIndex=j;
        }
        swap(vec[minIndex], vec[i]);
    }
}



/* Quicksort algorithm */
int partition(Vector<int> &vec, int start, int end){
    int lh = start +1;
    int rh = end;
    int pivotVal = vec[start];

    while (true){
        while (rh>lh && vec[rh]>=pivotVal) rh--;
        while (lh<rh && vec[lh]<pivotVal) lh++;
        if (lh==rh) break;
        swap(vec[lh], vec[rh]);
    }

    if (pivotVal<=vec[lh]) return start;
    swap(vec[start], vec[lh]);
    return lh;
}



void quickSort(Vector<int> &vec, int start, int end){
    if(start<end){
        int pivotIndex = partition(vec, start, end);
        quickSort(vec, start, pivotIndex-1);
        quickSort(vec, pivotIndex+1, end);
    }
}



/* Support function to find median of three in a vector and places it at the zero index of that vector */
void medianOfThree(Vector<int> &vec, int start, int end){
    int midIndex = (start+end)/2;

    int first = vec[start];
    int mid = vec[midIndex];
    int last = vec[end];

    // find the median an place it at the start index
    if (first < mid && mid <last){
        swap(vec[midIndex], vec[start]);
        return;
    }
    else if (first < last && last < mid){
        swap (vec[start], vec[end]);
        return;
    }
    else if (first > mid && mid > last){
        swap (vec[midIndex], vec[start]);
        return;
    }
    else if (first > last && last > mid ){
        swap(vec[end], vec[start]);
        return;
    }
}



/* Recursive quicksort function that uses median of three */
void medianQuickSort(Vector<int> &vec, int start, int end){
    if (start < end){
        medianOfThree(vec, start, end);
        int pivot = partition(vec, start, end);
        medianQuickSort(vec, start, pivot-1);
        medianQuickSort(vec, pivot+1, end);
    }
}



/* Insertion sort algorithm, this algorithm sorts elements in an array between start and end */
void insertionSort(Vector<int> &vec, int start, int end){
    for (int i=start; i<end; i++){
        int j=i;
        while (j>start && vec[j-1]>vec[j]){
            swap(vec[j-1], vec[j]);
            j--;
        }
    }
}



/* Insertion sort algorithm, this function sorts the whole vector */
void insertionSortWholeVector(Vector<int> &vec){
    int size = vec.size();
    for (int i=0; i<size; i++){
        int j=i;
        while (j>0 && vec[j-1]>vec[j]){
            swap(vec[j-1], vec[j]);
            j--;
        }
    }
}



/* Hibrid quicksort & insertion sort, as soon as the part of the vector to sort becomes less than the
 * crossover value, the algorithm switches to insertion sort, otherwise it uses quicksort.
 * Specified in exercise 7 */
void hybridSort1(Vector<int> &vec, int start, int end, int crossover){
    if(start < end){
        if (end-start <= crossover){
            insertionSort(vec, start, end);
        } else {
            int pivotIndex = partition(vec, start, end);
            hybridSort1(vec, start, pivotIndex-1, crossover);
            hybridSort1(vec, pivotIndex+1, end, crossover);
        }
    }
}



/* Quicksort that sorts the vector until it hits a certain threshold, used to get the vector almost
 * sorted so that the rest of work was done with insertion sort */
void thresholdQuickSort(Vector<int> &vec, int start, int end, int threshold){
    if (end - start < threshold) return;
    else if (start< end){
        int pivotIndex = partition(vec, start, end);
        thresholdQuickSort(vec, start, pivotIndex-1, threshold);
        thresholdQuickSort(vec, pivotIndex+1, end, threshold);
    }
}



/* Hybrid sort as specified in exercise 8 */
void hybridSort2(Vector <int> &vec, int threshold){
    int start = 0;
    int end = vec.size()-1;
    thresholdQuickSort(vec,start, end, threshold);
    insertionSortWholeVector(vec);
}



/* Majority element as per exercise 13 */



int main() {

    Vector<int> vec {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 14, 39, 30, 83, 92, 41};
    int end = vec.size()-1;
    //medianQuickSort(vec, 0, end);
    //quickSort(vec, 0, end);
    //insertionSort(vec, 0, end);
    //selectionSort(vec);
    //hybridSort1(vec, 0, end, 5);
    //hybridSort2(vec, 3);


    cout << vec.toString() <<endl;




    return 0;




}

// do ex 13, 14

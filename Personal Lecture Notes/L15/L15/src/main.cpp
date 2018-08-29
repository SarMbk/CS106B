#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "map.h"
#include "set.h"
#include <cmath>
using namespace std;

void SelectionSort(Vector<int> &v){
    for (int i=0; i<v.size()-1; i++){
        int minIndex = i;
        for (int j=i+1; j<v.size(); j++){
            if (v[minIndex]>v[j]) minIndex=j;
        }
        swap(v[minIndex], v[i]);
    }
}

void InsertionSort(Vector<int> &v){
    int tmp;
    for (int i=1; i<v.size(); i++){
        int j=i;
        while(j>0 && v[j-1]>v[j]){
            tmp = v[j];
            v[j] = v[j-1];
            v[j-1] = tmp;
            j--;
        }
    }
}

void Merge (Vector<int> &v, Vector<int> &v1, Vector<int> &v2){
    int p, p1, p2;
    p=p1=p2=0;
    while (p1<v1.size() && p2<v2.size()){
        if (v1[p1] < v2[p2])
            v[p++] = v1[p1++];
        else
            v[p++] = v2[p2++];
    }
    while (p1<v1.size()) v[p++] = v1[p1++];
    while (p2<v2.size()) v[p++] = v2[p2++];
}


void MergeSort(Vector<int> &v){
    if (v.size()>1){
        int n1 = v.size()/2;
        int n2 = v.size() - n1;
        Vector<int> v1 = v.subList(0, n1);
        Vector<int> v2 = v.subList(n1, n2);
        MergeSort(v1);
        MergeSort(v2);
        Merge (v, v1, v2);
    }
}


int main() {

    Vector<int> vec {6, 5, 4, 7, 3, 2, 1};

    //SelectionSort(vec);
    //InsertionSort(vec);
    MergeSort(vec);

    cout<< vec.toString() << endl;


    return 0;

}

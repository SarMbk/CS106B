#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
using namespace std;


bool subsetSum(Vector<int> &nums, int target){
    if(nums.isEmpty()) return (target==0);
    else{
        int element = nums[0];
        Vector<int> rest =nums.subList(1, nums.size()-1);
        return ( subsetSum(rest, target-element) || subsetSum(rest, target));
    }
}


int main(){
    Vector<int> vec {-1, 2, 3, 4, 5};

   cout << boolToString(  subsetSum(vec, -1)  ) << endl;

    return 0;
}


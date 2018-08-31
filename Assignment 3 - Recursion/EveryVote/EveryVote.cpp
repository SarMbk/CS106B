#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


bool subsetSum(Vector<int> &nums, int target){
    if(nums.isEmpty()) return (target==0);
    else{
        int element = nums[0];
        Vector<int> rest =nums.subList(1, nums.size()-1);
        return ( subsetSum(rest, target-element) || subsetSum(rest, target));
    }
}


void criticalVotes(Vector<int> &blocksCopy, int checkVote, int &critical, int &total, int alice, int bob){
    if(blocksCopy.size()==0){
        if(abs(alice-bob)<=checkVote){
            critical++;
            total++;
        }
    }
    else{
        int vote = blocksCopy[0];
        Vector<int> rest = blocksCopy.subList(1, blocksCopy.size()-1);
        criticalVotes(rest, checkVote, critical, total, alice+vote, bob);
        criticalVotes(rest, checkVote, critical, total, alice, bob+vote);
    }
}


int countCriticalVotes(Vector<int> &blocks, int index){
    int checkVote = blocks[index];
    Vector<int> blocksCopy = blocks;
    blocksCopy.remove(index);

    int critical = 0;
    int total = 0;
    int alice = 0;
    int bob = 0;

    criticalVotes(blocksCopy,checkVote,critical,total,alice,bob);

    return critical;

}



int main(){
    Vector<int> blocks {4, 2, 7, 4};
    cout << countCriticalVotes(blocks, 3) << endl;


    Vector<int> blocks2 {9,9,7,3,1,1};
    cout << countCriticalVotes(blocks2, 5) << endl;

    return 0;
}


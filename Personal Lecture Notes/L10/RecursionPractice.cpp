#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "set.h"
using namespace std;



// RecFactorial
int recFactorial (int n){
    if (n==0) return 1;
    else{
        //cout<< n << "*" <<n-1 << "!"<< endl;
        return n*recFactorial(n-1);
    }
}

// Fibonacci
int fib(int n){
    if (n==0) return 0;
    if (n==1) return 1;
    else {
        //cout << "fib(" << n-1 << ") + " <<"fib(" << n-2 << ")" << endl;
        return fib(n-1)+fib(n-2);
    }
}

//Additive sequence - fibonacci sequence with defined first two terms, i.e. generalized fibonacci
int additiveSequence (int n, int t0, int t1){
    if(n==0) return t0;
    if(n==1) return t1;
    else return additiveSequence(n-1, t0, t1)+additiveSequence(n-2, t0, t1);
}

//using fibonacci trough a wrapper function and a generalized case
int fibAdditive(int n){
    return additiveSequence (n, 0, 1);
}

//Recursive Palindrome
bool isPalindrome(string s){
    int len = s.length();
    if (s.length()==0) return true;
    if (s.length()==1) return true;
    else{
        return s[0]==s[len-1] && isPalindrome(s.substr(1,len-2));
    }
}

// Efficient recursive palindrome
bool isPalindromeEfficient(string s, int p1, int p2){
    if (p2-p1==0 || p2-p1==1) return true; //p2-p1==0 - empty string, p2-p1==1 - single character string
    else return s[p1]==s[p2] && isPalindromeEfficient(s, p1+1, p2-1);
}
// Wrapper for isPalindromeEfficient
bool isPalindrome2(string s){
    return isPalindromeEfficient(s, 0, s.length()-1);
}


//binary search
int binarySearch (string key, Vector<string> &v, int p1, int p2){
    if (p1>p2) return -1;
    int mid = (p1+p2)/2;
    if (v[mid]==key) return mid;
    if (v[mid]>key) return binarySearch(key, v, p1, mid-1);
    else return binarySearch(key, v, mid+1, p2);
}
// This is a wrapper function
int findInSortedVector(string key, Vector<string> &v){
    return binarySearch(key, v, 0, v.size()-1);
}


// Raise to power
int recPower(int base, int exp){
    if (exp==0) return 1;
    else return base*recPower(base, exp-1);
}

// Greatest Common divisor, recursive
int GCD (int x, int y){
    if (x==y) return x;
    int larger, smaller;
    if (x>y) {larger = x; smaller = y;}
    if (x<y){larger = y; smaller = x;}

    if (larger%smaller==0) return smaller;
    else{
        return GCD(smaller, larger%smaller);
    }
}


// Recursive nCk (given n choose k; order not important)
int C(int given, int choose){
    if (given==choose) return 1;
    if (choose==0) return 1;
    else return C(given-1, choose-1) + C(given-1, choose);
}


// Recursive reverse string
string RecRevStr(string s){
    if (s.length()==1) return s;
    else{
        return RecRevStr( s.substr(1,s.length()-1) ) + s[0];
    }
}


// Towers of Hanoi
void moveSingleDisk(char start, char finish){
    cout << start << " -> " << finish << endl;
}
void moveTower(int n, char start, char finish, char temp){
    if (n==1) moveSingleDisk(start, finish);
    else{
        moveTower(n-1, start, temp, finish);
        moveSingleDisk(start, finish);
        moveTower(n-1, temp, finish, start);
    }
}

//Subset sum problem
bool subsetSumExists(Set<int> &nums, int target){
    if (nums.isEmpty()) return (target==0);
    else{
        int element = nums.first();
        Set<int> rest = nums-element;
        return ( subsetSumExists(rest, target-element) || subsetSumExists(rest, target) );
    }
}


//Generating recursive permutations
void RecPermute(string soFar, string rest){
    if (rest==""){
        cout << soFar << endl;;
    }
    else{
        for (int i=0; i< rest.length(); i++){
            string next = soFar+ rest[i];
            string remaining = rest.substr(0, i) + rest.substr(i+1);
            RecPermute(next, remaining);
        }
    }
}

// Wrapper
void ListPermutations(string s){
    return RecPermute("", s);
}

//Make a set of permutations
Set<string> genPermutations(string soFar, string rest){
    Set<string> result;
    if (rest==""){
        result.add(soFar);
    }
    else{
        for (int i=0; i<rest.length(); i++){
            string next = soFar + rest[i];
            string remaining = rest.substr(0,i) + rest.substr(i+1);
            Set<string> subResult = genPermutations(next, remaining);
            result += subResult;
        }
    }
    return result;
}
// Wrapper
Set<string> getSetPermutations(string s){
    return genPermutations("", s);
}


//EveryVote counts
void countCritical(Vector<int>blocksCopy, int targetBlock, int alice, int bob, int &total, int &critical){
    if(blocksCopy.size()==0){
        if(abs(alice-bob)<=targetBlock){
            total++;
            critical++;
        }
    }
    else{
        int next = blocksCopy[0];
        blocksCopy.remove(0);
        countCritical(blocksCopy, targetBlock, alice+next, bob, total, critical);
        countCritical(blocksCopy, targetBlock, alice, bob+next, total, critical);
    }
}
// Wrapper
int countCriticalVotes(Vector<int> &blocks, int index){
    int targetBlock = blocks[index];
    Vector<int>blocksCopy = blocks;
    blocksCopy.remove(index);
    int alice = 0;
    int bob = 0;
    int total = 0;
    int critical = 0;
    countCritical(blocksCopy,targetBlock, alice, bob, total, critical);
    return critical;
}


// Need function prototypes for mutually recursive functions
bool isEven(int n);
bool isOdd (int n);

int main(){

    cout << recFactorial(5)<< endl;

    cout << fib(12) << endl;

    cout << additiveSequence(6, 3, 7)<< endl;

    cout << fibAdditive(12) << endl;

    cout << boolToString( isPalindrome("level") ) << endl;

    cout << boolToString( isPalindrome2("level") ) << endl;

    Vector<string> abc {"a", "b", "c", "d", "e", "f", "g", "h", "i"};

    cout << findInSortedVector("h", abc) << endl;

    cout << boolToString( isEven(99999) ) << endl;

    cout << recPower(3, 4) << endl;

    cout << GCD(480, 150) << endl;

    cout << C(128,2) << endl;

    cout << RecRevStr("1234567890abcdefghijklmnopqrstuvwxyz") << endl;

    cout << endl << endl << endl;
    cout << "Hanoi" << endl;

    moveTower(4, 'L','M', 'R'); // left middle right - hanoi problem

    Set<int> nums {1, -2, 3, 4, 5};
    cout << boolToString( subsetSumExists(nums, -1) ) << endl; // subset sum problem

    cout << "RecPermute"<<endl<<endl;

    ListPermutations("ABC");
    Set<string> perms = getSetPermutations("abc");
    cout << perms.toString() << endl;

    Vector<int> votes {4,3,7,4};
    cout << countCriticalVotes(votes, 0) << endl;



    return 0;
}



// Odd and even numbers mutual recursion
bool isEven(int n){
    if (n==0) return true;
    else return isOdd(n-1);
}
bool isOdd (int n){
    return (!isEven(n));
}

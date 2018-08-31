#include <iostream>
#include <map>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include <math.h>
#include "fstream"
#include "set.h"
#include "random.h"
using namespace std;


// ================= MAPS ======================== //
/*
void ReadFile(ifstream &in, map<string,int> &m){
    while(true){
        string word;
        in >> word;
        if(in.fail()) break;
        if(m[word]==0){
            m[word]=1;
        } else {
            m[word]+=1;
        }
    }

    int maxCount = 0;
    string mostFrequent = "";
    for ( map<string,int>::iterator it = m.begin(); it!=m.end(); ++it){
        if(it->second > maxCount){
            maxCount = it->second;
            mostFrequent = it->first;
        }
        cout << it->first << ": " << it->second <<endl;
    }

    cout <<"Most frequent word: " << mostFrequent << "; " << maxCount << " occurences." << endl;

}



int main(){
    ifstream in("readme.txt");
    map <string, int> wordCounts;
    ReadFile(in, wordCounts);
    return 0;
}
*/


/*  ============= PLAYING WITH VECTORS ==================
//trying out vectors
int main(){
    Vector<string> v;
    v.add("zero");
    v.add("one");
    v.add("two");
    cout << v.toString() << endl;

    v.remove(1);
    cout << v.toString();




    return 0;
}
*/




// ================ SETS ================= //

/*
void testRandom(){
    Set<int> seen;
    while (true){
        int num = randomInteger(0,100);
        if (seen.contains(num)) break;
        seen.add(num);
    }
    cout <<"unique random nums: " << seen.size() << endl;
    Set<int>::iterator it;
    for (it = seen.begin(); it != seen.end(); it++) {
        cout << *it << endl;
    }
}



int main(){
    testRandom();
    return 0;
}

*/




// Frends and enemies
struct person {
    string name;
    Set <string> friends, enemies;
};


Set<string> makeGuestList (person one, person two){
    Set<string> result = one.friends;
    result.operator +=(two.friends);
    result.operator -=(one.enemies);
    result.operator -=(two.enemies);
    return result;
}

int main (){
    person X;
    person Y;

    X.friends+= "Tom";
    X.friends+= "Bob";
    X.friends+= "Pat";
    X.friends+= "Sam";
    X.friends+= "Mal";

    X.enemies+= "Bad guy";

    Y.friends+= "Tom";
    Y.friends+= "Bob";
    Y.friends+= "Katie";
    Y.friends+="Sar";

    Y.enemies+= "Bad guy 2";

    Set<string> list = makeGuestList(X, Y);

    cout << list.toString() << endl;

    return 0;
}

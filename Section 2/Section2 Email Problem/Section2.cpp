#include <iostream>
#include "console.h"
#include "gwindow.h" // for GWindow
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
using namespace std;


/* STRUCTURE DEFINITIONS */
struct emailMsg{
    string to;
    string from;
    string message;
    string subject;
    int date;
    int time;
};


struct multEmailMsg{
    Vector<string> to;
    string from;
    string message;
    string subject;
    int date;
    int time;
};


/* FUNCTION PROTOTYPES */
void RemoveSpam(Vector<emailMsg> &v);



/* MAIN METHOD */
int main(){

    // Create several trial objects of type emailMsg
    emailMsg m0;
    m0.to = "Kizimke";
    m0.from = "Saruar";
    m0.message = "Hollaaay";
    m0.subject = "Hav ar ju m0";
    m0.date = 1;
    m0.time = 1;

    emailMsg m1;
    m1.to = "Kizimke";
    m1.from = "Saruar";
    m1.message = "Hollaaay";
    m1.subject = "SPAM Hav ar ju m1";
    m1.date = 1;
    m1.time = 1;

    emailMsg m2;
    m2.to = "Kizimke";
    m2.from = "Saruar";
    m2.message = "Hollaaay";
    m2.subject = "Hav ar SPAM ju m2";
    m2.date = 1;
    m2.time = 1;

    // Declare a vector of type emailMsg and add emails to it
    Vector<emailMsg> vec;
    vec.add(m0);
    vec.add(m1);
    vec.add(m2);

    // Remove spam
    RemoveSpam(vec);


    // Creating emails of type multEmailMsg
    multEmailMsg mult1;
    mult1.to.add("recipient1");
    mult1.to.add("recipient 2");
    mult1.from = "sar";
    mult1.message = "Hollaaay";
    mult1.subject = "random subject";
    mult1.date = 1;
    mult1.time = 1;

    // Vector containg all emails
    Vector <multEmailMsg> vecMult;
    vecMult.add(mult1);

    //Access last recipient from a multiple vector;
    //cout << vecMult[0].to.get( vecMult[0].to.size()-1 )  << endl;
    //Above line is hard to read. Broken into two lines below
    int lastEmailIndex = vecMult[0].to.size()-1;
    cout << vecMult[0].to.get( lastEmailIndex );

    return 0;   
}


/* FUNCTION DEFINITIONS */
void RemoveSpam(Vector<emailMsg> &v){
    for (int i = v.size()-1; i>=0; i--){
        emailMsg msg =v.get(i);
        if(   msg.subject.find("SPAM") != string::npos  ){
            cout << "deleted message with subject: " << msg.subject << endl;
            v.remove(i);
        }
    }
}




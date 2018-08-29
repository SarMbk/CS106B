#include <iostream>
using namespace std;


class Car
{
public:
    Car(string carName, int weight, int numAirbags);
    string getName();
    int getWeight();
    int getNumAirbags();
    string toString();
    bool operator ==(Car &c);

private:
    string name; int weight; int numAirbags;
};

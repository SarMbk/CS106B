#include "car.h"

Car::Car(string carName, int weight, int numAirbags){
    this->name = carName;
    this->weight = weight;
    this->numAirbags = numAirbags;
}

string Car::getName(){
    return this->name;
}

int Car::getWeight(){
    return this->weight;
}

int Car::getNumAirbags(){
    return this->getNumAirbags();
}

string Car::toString(){
    return "name:" + name + "  weight:" + std::to_string(weight)+
           "  numAirbags:" + std::to_string(numAirbags);
}

bool Car:: operator==(Car &c){
    return name==c.getName() && weight==c.getWeight() && numAirbags==c.getNumAirbags();
}



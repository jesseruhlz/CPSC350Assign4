#include <iostream>
#include "Student.h"
using namespace std;

Student::Student(){
  timeAtWindow = 0;
  entry = 0;
  timeInQueue = 0;
  idle = 0;
}

Student::~Student(){

}

Student::Student(int t, int e){
  timeAtWindow = t;
  entry = e;
  timeInQueue = 0;
  idle = 0;
}

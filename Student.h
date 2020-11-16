#include <iostream>
using namespace std;

class Student
{
  public:
    Student();
    ~Student();
    Student(int t, int e);

    int timeAtWindow;
    int entry;
    int timeInQueue;
    int idle;
};

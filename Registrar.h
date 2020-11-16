#include <string>
#include <iostream>
#include "Queue.h"
#include "Student.h"
using namespace std;

class Registrar{
  public:
    Registrar();
    ~Registrar();

    bool readFile(string f);
    bool incrementTime(int iT);

    double meanWait();
    double medianWait();
    int longestWait();
    int numStudOverTen();

    string getMinuteMess();
    void minuteMessage(int m);
    string studentMessage();

    int meanIdle();
    int longestIdle();
    int numIdleOverFive();

    Student* *windowArray;
    Queue<Student*> studentQueue;

    Queue<int> waitTime;
    Queue<int> idleTime;

    int *medianArr;
    int *idleArr;

    int totalWindows;
    int totalStuds;
    bool showFile;

  private:
    int lineType;
    int entryTime;
    int StudentTimeAtWindow;
    int studAtTime;
    int medianCount;
    int idleCount;
    string messageString;
};

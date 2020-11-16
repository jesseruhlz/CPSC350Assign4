#include <iostream>
#include "Registrar.h"
int main(int argc, char *argv[])
{
  /*
  string line;
  int value;
  string fileName;
  int count = 0;

  cout << "Enter a location of a .txt file" << endl;
  cout << "Format should be like ../TestFile/file.txt" << endl;
  cin >> fileName;
  ifstream infile;
  infile.open(fileName);

  if(!infile){
    cout << "ERROR opening file." << endl;
  }

  //setup inserBack function from the template
  //DoublyList<int> insert;
  Queue<int> input;
  //while the file reads in a number,
  while(infile >> value){
    //count++;
    //insert the read number into the doubly linked list
    //insert.insertBack(value); //only inserts 5 into the list six times
    input.enqueue(value);
  }
  cout << "Our doubly list of registrar office data is: " << endl;
  //insert.printList();
  input.printQueue();
  */

  Registrar r;
  int currentTime = 0;
  int openWindows = 0;
  bool endRun = false;


  if (argc == 2){
    if (r.readFile(argv[1])){
      while (!endRun){
        if (r.studentQueue.isEmpty()){
          int t = 0;
          for (int i = 0; i < r.totalWindows; ++i){
            if ((r.windowArray[i]->timeAtWindow) < 1){
              t++;
            }
          }
          if (t == r.totalWindows)
            endRun = true;
        }

        for (int i = 0; i < r.totalWindows; ++i){
          if (r.windowArray[i]->timeAtWindow < 1){
            if (!r.studentQueue.isEmpty()){
              Student* s = r.studentQueue.getFront();
              if (s->entry <= currentTime){
                if (r.windowArray[i]->idle > 0){
                  r.idleTime.enqueue(r.windowArray[i]->idle);
                }
                r.windowArray[i] = r.studentQueue.dequeue();
                r.waitTime.enqueue(r.windowArray[i]->timeInQueue);
              }
            }
          }
        }
        currentTime++;
        r.incrementTime(currentTime);
      }
      for (int i = 0; i < r.totalWindows; ++i){
        if (r.windowArray[i]->idle > 0)
          r.idleTime.enqueue(r.windowArray[i]->idle);
      }
      r.minuteMessage(currentTime);
      cout << "The mean student wait time: " << r.meanWait() << " minute(s)." << endl;
      cout << "The median student wait time: " << r.medianWait() << " minute(s)." << endl;
      cout << "The longest student wait time: " << r.longestWait() << " minute(s)." << endl;
      cout << "Students waiting over 10 minutes " << r.numStudOverTen() << " student(s)." << endl;
      cout << "The mean window idle time:  " << r.meanIdle() << " minute(s)." << endl;
      cout << "The longest window idle time: " << r.longestIdle() << " minute(s)." << endl;
      cout << "Number of windows idle over 5 minutes: " << r.numIdleOverFive() << " window(s)." << endl;
    }
    else{
      if (r.showFile){
        cout << "Error opening file." << endl;
      }
    }
  }
  else{
    cout << "Enter location of a file name in command line." << endl << endl;
  }
  /*
  (r.readFile("GivenCase01.txt"));
  while (!endRun){
    if (r.studentQueue.isEmpty()){
      int t = 0;
      for (int i = 0; i < r.totalWindows; ++i){
        //opem window
        //cout << "opening window" << endl;
        if ((r.windowArray[i]->timeAtWindow) < 1){
          t++;
        }
      }
      if (t == r.totalWindows)
        endRun = true;
    }
    //sending student 1 from queu to window
    for (int i = 0; i < r.totalWindows; ++i){
      //open window
      if (r.windowArray[i]->timeAtWindow < 1){
        //student in queue
        if (!r.studentQueue.isEmpty()){
          Student* s = r.studentQueue.getFront();
          if (s->entry <= currentTime){
            if (r.windowArray[i]->idle > 0){
              r.idleTime.enqueue(r.windowArray[i]->idle);
            }
            //take student from queue to window
            r.windowArray[i] = r.studentQueue.dequeue();
            r.waitTime.enqueue(r.windowArray[i]->timeInQueue);
          }
        }
      }
    }
    currentTime++;
    r.incrementTime(currentTime);
  }
  for (int i = 0; i < r.totalWindows; ++i){
    if (r.windowArray[i]->idle > 0)
      r.idleTime.enqueue(r.windowArray[i]->idle);
  }
  r.minuteMessage(currentTime);
  cout << "Mean student wait time: " << r.meanWait() << r.getMinuteMess() << endl;
  cout << "Median wait time: " << r.medianWait() << " minte(s)." << endl;
  cout << "Longest wait time: " << r.longestWait() << " minute(s)." << endl;
  cout << "Students waiting over 10 minutes " << r.numStudOverTen() << " student(s)." << endl;
  cout << "Mean window idle: " << r.meanIdle() << " minute(s)." << endl;
  cout << "Longest window idle time: " << r.longestIdle() << " minute(s)." << endl;
  cout << "Idle time over 5 minutes: " << r.numIdleOverFive() << " minute(s)." << endl;
  */
  return 0;
}
